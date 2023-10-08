#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 33333

int main() {
    // 创建套接字
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
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

    // 连接服务器
    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    // 获取本地套接字地址信息
    struct sockaddr_in localAddr;
    socklen_t localAddrLen = sizeof(localAddr);
    if (getsockname(sockfd, (struct sockaddr*)&localAddr, &localAddrLen) == -1) {
        perror("getsockname");
        exit(EXIT_FAILURE);
    }

    // 获取对端套接字地址信息
    struct sockaddr_in peerAddr;
    socklen_t peerAddrLen = sizeof(peerAddr);
    if (getpeername(sockfd, (struct sockaddr*)&peerAddr, &peerAddrLen) == -1) {
        perror("getpeername");
        exit(EXIT_FAILURE);
    }

    // 打印本地套接字地址信息
    char localIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(localAddr.sin_addr), localIP, sizeof(localIP));
    printf("Local address: %s:%d\n", localIP, ntohs(localAddr.sin_port));

    // 打印对端套接字地址信息
    char peerIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(peerAddr.sin_addr), peerIP, sizeof(peerIP));
    printf("Peer address: %s:%d\n", peerIP, ntohs(peerAddr.sin_port));

    // 关闭套接字
    close(sockfd);

    return 0;
}
