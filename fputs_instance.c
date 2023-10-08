#include <stdio.h>

int main()
{
    char str[] = "Hello, world!\n";
    FILE *fp;

    fp = fopen("test.txt", "w+");
    if (fp == NULL) {
        perror("Failed to open file test.txt");
        return -1;
    }

    fputs(str, fp);

    fclose(fp);

    return 0;
}
