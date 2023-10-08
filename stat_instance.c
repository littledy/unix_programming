#include <stdio.h>
#include <sys/stat.h>

int main() {
    struct stat file_stat;
    int ret = stat("test.txt", &file_stat);
    if (ret == 0) {
        printf("File size: %ld bytes\n", file_stat.st_size);
        printf("File permission: %o\n", file_stat.st_mode & 0777);
    } else {
        printf("Failed to get file stat\n");
    }
    return 0;
}
