
#include "safe-fork.h"
#include "split.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

/* This program will act simmilar to xargs utility. This program will gets
program name and argument using argv[] and execute based on the "-n" option.
If there is -n option given, it will just print all the given argument, if
not it will create a new process and use execvp to change a process and execute
the given argument. If there is no target program or errors occur it will 
quit immediately. */
int main(int argc, char * argv[]) {
  char * target_program;
  char ** arguments = NULL;
  int print_only = 0;
  char line[10000];
  int i = 0;
  char ** words = NULL;
  pid_t pid;
  char ** args;
  int word_count = 0;
  int exit_status = 0;

  /* Determine if the -n argument was used */
  if (argc > 1 && strcmp(argv[1], "-n") == 0) {
    print_only = 1;
  }

  /* If there is no -n in argument, it will save given argument into \
     arguments*/
  if (!print_only && argc > 1) {
    target_program = argv[1];
    if (argc > 2) {
      /* If there is argument save into argument variable */
      arguments = malloc((argc - 2) * sizeof(char * ));
      for (i = 1; i < argc - 1; i++) {
        arguments[i - 1] = argv[i + 1];
      }
    }
  }

  /* If it is print_only option, it should stardard input using fgets and 
split the input using split function.After that prints all the argument and
given input and free the memory */
  if (print_only) {
    while (fgets(line, 10000, stdin) != NULL) {
      /*get input */
      words = split(line); /* Split input */

      /* Print argument */
      for (i = 2; i < argc; i++) {
        if (i < argc - 1)
          printf("%s ", argv[i]);
        else
          printf("%s", argv[i]);
      }

      /* Print input */
      for (i = 0; words[i] != NULL; i++) {
        printf(" %s", words[i]);
      }
      printf("\n");

      /* Free allcated memory */
      if (words != NULL)
        for (i = 0; words[i] != NULL; i++)
          free(words[i]);
      free(words);
    }
  }

  /* If there is no "-n" option gets argument and input. And using saved 
arguments and input execute by creating new prgress using safe_fork.
If the error exist or the child process do not terminate well, should 
return the exit status.  */
  if (!print_only) {
    while (fgets(line, 10000, stdin) != NULL) {
      /*get input */
      words = split(line); /* split input */
      pid = safe_fork(); /* fork child */

      /* Parent process execution */
      if (pid > 0) {
        wait( & exit_status); /*wait for child to terminate */

        /* If the child did not exit well should return the exit status */
        if (WIFEXITED(exit_status) && WEXITSTATUS(exit_status) != 0) {
          if (words != NULL) {
	    /*Free memories */
            for (i = 0; words[i] != NULL; i++)
              free(words[i]);
            free(words);
          } 
          if (arguments != NULL)
            free(arguments);
          return WEXITSTATUS(exit_status);
        }

        /* Free all the allocated memory */
        if (words != NULL) {
          for (i = 0; words[i] != NULL; i++)
            free(words[i]);
          free(words);
        }
        words = NULL;
      }

      /* Child process Execution */
      if (pid == 0) {
        word_count = 0;

        /* Count input number */
        while (words[word_count] != NULL) {
          word_count++;
        }

        /* Allocate memory for all arguments and input */
        args = malloc((argc + word_count) * sizeof(char * ));
        args[0] = target_program; /* first argument is target_program */
        /* Save all the argument into args[]*/
        if (arguments != NULL) {
          for (i = 1; i < argc - 1; i++) {
            args[i] = arguments[i - 1];
          }
        }

        /* Save all the input in the end of args */
        for (i = 0; i < word_count; i++) {
          args[argc + i - 1] = words[i];
        }

        /*Set last element NULL */
        args[argc + word_count - 1] = NULL;
        execvp(args[0], args); /* executes as a new process using args */

        /* Free and exit */
        if (args != NULL)
          free(args);
        if (words != NULL) {
          for (i = 0; words[i] != NULL; i++)
            free(words[i]);
          free(words);
        }
        if (arguments != NULL)
          free(arguments);
        exit(255);
      }
    }
  }

  /* Free and return 0 */
  if (arguments != NULL)
    free(arguments);
  return 0;
}
