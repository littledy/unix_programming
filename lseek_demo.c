#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    ssize_t len = read(fd, buffer, sizeof(buffer));
    if (len == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // 将文件指针移动到文件开头
    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek");
        exit(EXIT_FAILURE);
    }

    len = read(fd, buffer, sizeof(buffer));
    if (len == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    printf("Read data: %.*s\n", (int) len, buffer);

    if (lseek(fd, -5, SEEK_CUR) == -1) {
        perror("lseek");
        exit(EXIT_FAILURE);
    }
    len = read(fd, buffer, sizeof(buffer));
    if (len == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    printf("Read data: %.*s\n", (int) len, buffer);

    close(fd);
    return 0;
}