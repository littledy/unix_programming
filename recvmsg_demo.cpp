#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/uio.h>

#define MAX_BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 33334

// sendmsg and recvmsg function
int main() {
    // 创建套接字
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址信息
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    if (inet_pton(AF_INET, SERVER_IP, &(serverAddr.sin_addr)) <= 0) {
        perror("inet_pton");
        exit(EXIT_FAILURE);
    }

    // 构造发送消息
    const char* message = "Hello, server!";
    struct iovec iov;
    iov.iov_base = (void*)message;
    iov.iov_len = strlen(message);

    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));
    msg.msg_name = (struct sockaddr*)&serverAddr;
    msg.msg_namelen = sizeof(serverAddr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    // 发送消息到服务器
    ssize_t sendSize = sendmsg(sockfd, &msg, 0);
    if (sendSize == -1) {
        perror("sendmsg");
        exit(EXIT_FAILURE);
    }

    // 接收服务器响应
    char buffer[MAX_BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));

    struct iovec iov_recv;
    iov_recv.iov_base = buffer;
    iov_recv.iov_len = sizeof(buffer);

    struct msghdr msg_recv;
    memset(&msg_recv, 0, sizeof(msg_recv));
    msg_recv.msg_name = NULL;
    msg_recv.msg_namelen = 0;
    msg_recv.msg_iov = &iov_recv;
    msg_recv.msg_iovlen = 1;

    ssize_t recvSize = recvmsg(sockfd, &msg_recv, 0);
    if (recvSize == -1) {
        perror("recvmsg");
        exit(EXIT_FAILURE);
    }

    // 处理接收到的数据
    printf("Received from server: %s\n", buffer);

    // 关闭套接字
    close(sockfd);

    return 0;
}
