#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <poll.h>

int main() {
    struct pollfd fds[1];   // create plllfd struct with each element representing fd
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN; // event is read

    printf("Waiting for input...\n");

    int result = poll(fds, 1, -1);  // -1 represents waiting all the time
    if (result == -1) {
        perror("poll");
        return -1;
    } else {
        if (fds[0].revents & POLLIN) {
            printf("Data is available on stdin. You can start reading.\n");
            // read data
            char buffer[256];
            memset(buffer, 0, sizeof(buffer));
            read(STDIN_FILENO, buffer, sizeof(buffer));
            printf("Received data: %s\n", buffer);
        }
    }
    return 0;
}