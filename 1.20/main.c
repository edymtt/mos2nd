 /* file minunit_example.c */
 
 #include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

 #include "minunit.h"

 int tests_run = 0;
 
static int writeFile();
 static char* build_failure_message(const char* explanation);

 static char * test_fseek() {
     mu_assert(build_failure_message("error in creating file"), 
writeFile()>=0);
     int fileDescr=open("input.bin", O_RDONLY);
     mu_assert(build_failure_message("error in opening file"), 
fileDescr>=0);
     
     char buffer[4];
     bzero(buffer, 4);
     lseek(fileDescr,3, SEEK_SET);
     ssize_t bytesRead=read(fileDescr, buffer, 4);
     mu_assert(build_failure_message("error in reading file"), 
bytesRead==4);
     
printf("buffer content %i %i %i %i\n", buffer[0], buffer[1], buffer[2], 
buffer[3]);
mu_assert(build_failure_message("wrong content"), buffer[0]==1 && buffer[1]==5 && buffer[2] && buffer[3]);

     close(fileDescr);
     return 0;
 }
 
 static int writeFile() {
     if(remove("input.bin")<0 && errno != ENOENT)
     {
        return -1;
     }

     int fileDescr=open("input.bin", O_CREAT | O_EXCL | O_WRONLY);
     if(fileDescr<0)
     {
        return -1;
     }

     char buffer[11]={3,1,4,1,5,9,2,6,5,3,5};
     ssize_t numBytesWritten=write(fileDescr,buffer,11);
     if(numBytesWritten<0)
     {
printf("Error");
       return -1;
     }

     return close(fileDescr);
 }

 static char* build_failure_message(const char* explanation)
{
     char* failing_assert=(char*)malloc(100*sizeof(char));
     if(sprintf(failing_assert, "%s: %s",
       explanation,
strerror(errno))<0) 
{
       return "unable to sprintf";
}  
return failing_assert;
}

 
 static char * all_tests() {
     mu_run_test(test_fseek);
     return 0;
 }
 
 int main(int argc, char **argv) {
     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
         printf("ALL TESTS PASSED\n");
     }
     printf("Tests run: %d\n", tests_run);
 
     return result != 0;
 }
