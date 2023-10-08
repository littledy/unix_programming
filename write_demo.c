#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char buf[] = "Hello, world!\n";
    int bytes_written = write(fd, buf, sizeof(buf));
    if (bytes_written < 0) {
        perror("write");
        close(fd);
        return 1;
    }

    close(fd);
    return 0;
}