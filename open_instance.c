#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("test2.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char* data = "Hello, Nanjing!";
    int len = write(fd, data, strlen(data));
    if (len == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    close(fd);
    return 0;
}