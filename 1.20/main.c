 /* file minunit_example.c */
 
 #include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

 #include "minunit.h"

 int tests_run = 0;
  
 static char * test_fseek() {
     int fileDescr=open("input.bin", O_RDONLY);
     mu_assert("error in opening file", fileDescr>=0);
     close(fileDescr);
     return 0;
 }
 
 static void writeFile() {
     
 }
 
 static char * all_tests() {
     writeFile();
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
