/*Name : Kyumin Hwang
University Directory ID: khwang77
Nine-digits ID : 119134092
Section number : 0205
I pledge on my honor that I have not given or received any unauthorized
  assistance on this assignment*/

/* This program will check for lines in its input that are more than 
80 characters.It reads one input line and save a line into the array and
 checks the length of the line. If the line is more than 80 characters,
 It should print * in the beginning of the output.If not,
 just blank space should be printed */

/* Also for the line with more than 80 characters, this program will 
create a new line and indicates parts that are longer than 80 using ^ */

#include <stdio.h>

/* main method that will operate used to check the length of the line and 
   prints the line to check if the line exceed 80 chracters*/
int main(void) {
   /* list that saves up a line into a character list*/
   char line[1000];
   int number = 0; /* interger value that saves word number in a line*/
   int j = 0; /* integer value that will be used for for loop*/
   char word; /* temporary character value that will store a word from line */
   int line_number = 1; /* integer value that will be used to trace line 
number*/
   int end_of_input = 0; /* integer value to use in escaping while loop*/

   /* While loop to scan texts until it reach the end*/
   while (!end_of_input) {
      number = 0;
      /* Inner while loop to scan one line until end of the line*/
      /* run untils it finds '\n'*/
      while (!feof(stdin) && scanf("%c", & word) == 1 && word != '\n') {
         line[number] = word;
         /* if there is a tab increase the line length into eighth character.*/
         if (word == '\t') {
            if (number % 8 == 0)
               number += 8;
            else {
	      while (!(number % 8) == 0)
                  number++;
            }
         } else
            number++;

      }
      /* Null chracter that tells the end of the line when you print */
      line[number] = '\0';
      /* Prints the lien stored in the array*/
      if (!feof(stdin)) {
         /* If the character is more than 80 character print *at the beginning
          of the line*/
         if (number > 80) {
            printf("*%5d: ", line_number);
            for (j = 0; j < number; j++) {
               printf("%c", line[j]);
               /* If it meet tab character, should jump in the array to 
                  avoid garbage value*/
               if (line[j] == '\t') {
                  if (j % 8 == 0)
                     j = j + 7;
                  else {
		    while (!(j % 8) == 0)
                        j++;
                     j--;
                  }
               }
            }
            printf("\n");
            /* Make a new line and full it with spaces until 88 characters*/
            line_number++;
            for (j = 0; j < 88; j++) {
               printf(" ");
            }
            /* Prints ^ from the point where it exceed 80 characters*/
            for (j = 0; j < number - 80; j++) {
               printf("^");
            }
            printf("\n");
            /* If a line is not longer than 80 chracters just print 
             a line with a line number*/
         } else {
            printf(" %5d: ", line_number);
            for (j = 0; j < number; j++) {
               printf("%c", line[j]);
            }
            printf("\n");
            line_number++;
         }
      }
      /* Use to escape the while loop */
      if (feof(stdin))
         end_of_input = 1;
   }
   return 0;
}
