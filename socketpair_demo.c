#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>

int main() {
    int sockfd[2];

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sockfd) == -1) {
        perror("socketpair");
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        // Child process
        close(sockfd[0]);
        dprintf(sockfd[1], "Hello from child process fd: %d!\n", sockfd[1]);
        close(sockfd[1]);
    } else {
        // Parent process
        close(sockfd[1]);
        char buffer[1024];
        ssize_t numBytes = read(sockfd[0], buffer, sizeof(buffer));
        if (numBytes == -1) {
            perror("read");
            return 1;
        }
        printf("Message from child process: %.*s", (int)numBytes, buffer);
        close(sockfd[0]);
    }

    return 0;
}
