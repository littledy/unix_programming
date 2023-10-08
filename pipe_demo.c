#include <stdio.h>
#include <unistd.h>

int main() {
    int fds[2];

    if (pipe(fds) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process
        close(fds[0]);
        dprintf(fds[1], "Hello from child process fd: %d!\n", fds[1]);
        close(fds[1]);
    } else {
        // Parent process
        close(fds[1]);
        char buffer[1024];
        ssize_t numBytes = read(fds[0], buffer, sizeof(buffer));
        if (numBytes == -1) {
            perror("read");
            return 1;
        }
        printf("Message from child process: %.*s", (int)numBytes, buffer);
        close(fds[0]);
    }

    return 0;
}
