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

    printf("Read data: %.*s\n", (int) len, buffer);

    close(fd);
    return 0;
}