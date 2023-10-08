#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

void sigio_handler(int signo)
{
    if (signo == SIGIO) {
        printf("Received SIGIO signal. File descriptor is ready for I/O.\n");
        // 在这里处理异步I/O事件
    }
}

int main()
{
    // 打开文件
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // 设置文件描述符的属主进程为当前进程
    if (fcntl(fd, F_SETOWN, getpid()) == -1) {
        perror("Failed to set process as owner of the file descriptor");
        return 1;
    }

    // 文件描述符为非阻塞模式
    int flags = fcntl(fd, F_GETFL);
    if (flags == -1) {
        perror("Failed to get file descriptor flags");
        return 1;
    }
    flags |= O_ASYNC;
    if (fcntl(fd, F_SETFL, flags) == -1) {
        perror("Failed to set file descriptor flags");
        return 1;
    }

    // 设置信号处理程序
    struct sigaction sa;
    sa.sa_handler = sigio_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGIO, &sa, NULL) == -1) {
        perror("Failed to set signal handler");
        return 1;
    }

    char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    ssize_t bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer)-1);
    if (bytes_read == -1) {
        perror("read");
        return 1;
    }
    printf("Read %zd bytes: %s\n", bytes_read, buffer);

    // 关闭文件
    close(fd);

    return 0;
}
