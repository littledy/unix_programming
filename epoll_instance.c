#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>

#define MAX_EVENTS 5
#define READ_SIZE 10

int main() {
    int running = 1, event_count;
    struct epoll_event event, events[MAX_EVENTS];
    char buffer[READ_SIZE + 1];

    // 创建 epoll 实例
    int epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        return EXIT_FAILURE;
    }

    // 设置事件
    event.events = EPOLLIN;
    event.data.fd = STDIN_FILENO;

    // 将 stdin 注册到 epoll 实例
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event) == -1) {
        perror("epoll_ctl EPOLL_CTL_ADD");
        return EXIT_FAILURE;
    }

    while (running) {
        // 监听 epoll 事件
        event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (event_count == -1) {
            perror("epoll_wait");
            return EXIT_FAILURE;
        }

        // 处理事件
        for (int i = 0; i < event_count; i++) {
            // 如果事件是来自 stdin 的输入
            if (events[i].data.fd == STDIN_FILENO) {
                printf("stdin is readable\n");
                int bytes_read = read(STDIN_FILENO, buffer, READ_SIZE);
                if (bytes_read == -1) {
                    perror("read");
                    running = 0;
                } else if (bytes_read == 0) {
                    running = 0;
                } else {
                    buffer[bytes_read] = '\0';
                    printf("read %d bytes: %s\n", bytes_read, buffer);
                }
            }
        }
    }

    // 关闭 epoll 实例
    if (close(epoll_fd) == -1) {
        perror("close");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}