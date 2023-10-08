#include <stdio.h>

int main() {
   FILE *fp;
   int c;

   fp = fopen("test.txt", "r");
   if (fp == NULL) {
      perror("Error opening file");
      return(-1);
   }

   while ((c = getc(fp)) != EOF) {
      putchar(c);
   }

   fclose(fp);
   return 0;
}