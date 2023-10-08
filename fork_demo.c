#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    pid_t child_pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    child_pid = fork();

    if (child_pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        execl("/bin/ls", "ls", "-l", "/tmp", NULL);
    } else {
        close(pipefd[1]);
        char buffer[256];
        ssize_t bytes_read = read(pipefd[0], buffer, sizeof(buffer));
        printf("Command output: \n%s\n", buffer);
    }

    return 0;
}