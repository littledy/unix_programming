#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/epoll.h>

int main() {
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        return -1;
    }

    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event) == -1) {
        perror("epoll_ctl");
        return -1;
    }

    struct epoll_event events[1];
    int num_events;

    while (1) {
        num_events = epoll_wait(epoll_fd, events, 1, -1);   // -1 represents waiting all the time
        if (num_events == -1) {
            perror("epoll_wait");
            return -1;
        }
        for (int i = 0; i < num_events; ++i) {
            if (events[i].data.fd == STDIN_FILENO && events[i].events & EPOLLIN) {
                printf("Data is available on stdin. You can start reading.\n");
                // read data
                char buffer[256];
                memset(buffer, 0, sizeof(buffer));
                read(STDIN_FILENO, buffer, sizeof(buffer)-1);
                printf("Received data: %s\n", buffer);
            }
        }
    }
    return 0;
}