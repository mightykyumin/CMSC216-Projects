#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <pthread.h>
static void *count_file(void *arg);

static void *count_file(void *arg){
 FILE *fp;
 int *total_count;
 char ch, next_ch, *filename;
 int lines=0,words=0,chars=0;

 filename =(char*) arg;
 total_count = malloc(sizeof(int)*3);
 assert(total_count !=NULL);
  
 fp= fopen(filename, "r");  /* open that file */
 /* silently ignore any problems trying to open files */
 if (fp != NULL) {
    
   lines= words= chars= 0;
   
   /* read each file one character at a time, until EOF */
   ch= fgetc(fp);
   while (!feof(fp)) {
     next_ch= fgetc(fp);  /* look ahead and get the next character */
     ungetc(next_ch, fp);  /* unread the next character (see Chapter 15) */

     /* update the counts as needed every time a character is read */

     /* a newline means the line count increases */
     if (ch == '\n')
       lines++;

     /* if the current character is not whitespace but the next character
	is, or if the current character is not whitespace and it is the
	last character in the input, the word count increases */
     if (!isspace(ch) && (isspace(next_ch) || feof(fp)))
       words++;

     /* increasing the character count is a no-brainer */
     chars++;

     ch= fgetc(fp);
   }
   
   fclose(fp);
 }
 total_count[0]=lines;
 total_count[1]=words;
 total_count[2]=chars;
 return total_count;
}
int main(int argc, char *argv[]) {
  char *filename;
  int arg_num= 1, total_lines= 0, total_words= 0,
    total_chars= 0,i=0,*count_ptr;
  void *count_array;
  pthread_t *tids;
  
  if(argc >1){
    /* allocate tids */
    tids = malloc((argc-1)*sizeof(pthread_t));
    assert(tids!=NULL);
    for(i=0;i<argc-1;i++){
      filename= argv[arg_num++];
      assert(pthread_create(&tids[i],NULL,count_file,(void*)filename)==0);
    }
  
    for(i=0;i<argc-1;i++){
      assert(pthread_join(tids[i], &count_array) == 0);
      count_ptr = (int *) count_array;
    
      total_lines += count_ptr[0];
      total_words += count_ptr[1];
      total_chars += count_ptr[2];
      free(count_array);
    }
  
    free(tids);
    
  }
  printf("%4d %4d %4d\n", total_lines, total_words, total_chars);

  return 0;
}
