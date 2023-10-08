#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Hello, Nanjing!";
    char buffer[20] = {0};
    FILE *fp;

    fp = fopen("test.txt", "w+");
    if (fp == NULL) {
        perror("Failed to open file test.txt");
        return -1;
    }

    fwrite(str, sizeof(char), strlen(str), fp);
    fseek(fp, 0, SEEK_SET);
    fread(buffer, sizeof(char), strlen(str), fp);

    printf("Read from file: %s\n", buffer);

    fclose(fp);

    return 0;
}