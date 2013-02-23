 /* file minunit_example.c */
 
#include <stdio.h>

char* get_string()
{
  return "get_string\n";
}

int main(int argc, char **argv) {
  printf("Ciao\n");
  printf("%s", get_string());

  char fmt[50];
  sprintf(fmt, "%s",get_string());
  printf("%s",fmt);

  return 0;
 }
