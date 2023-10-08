#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

int main() {
    fd_set read_fds;    // read fd set
    FD_ZERO(&read_fds);
    FD_SET(STDIN_FILENO, &read_fds);    // add STDIN to read_fds

    struct timeval timeout;
    timeout.tv_sec = 5; // set timeout = 5s
    timeout.tv_usec = 0;

    printf("Waiting for input (5 seconds)...\n");

    int result = select(STDIN_FILENO+1, &read_fds, NULL, NULL, &timeout);
    if (result == -1) {
        perror("select");
        return -1;
    } else if (result == 0) {
        printf("Timeout! No data received.\n");
    } else {
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
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