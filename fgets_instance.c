#include <stdio.h>

int main() {
   FILE *fp;
   char buffer[1024];

   fp = fopen("test.txt", "r");
   if (fp == NULL) {
      perror("Error opening file");
      return(-1);
   }

   while (fgets(buffer, 1024, fp) != NULL) {
      printf("%s", buffer);
   }

   fclose(fp);
   return 0;
}
