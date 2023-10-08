#include <stdio.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 30

int main(int argc, char* argv[]) {
    struct iovec iov[2];
    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];
    ssize_t totalBytes;

    iov[0].iov_base = buffer1;
    iov[0].iov_len = BUFFER_SIZE;
    iov[1].iov_base = buffer2;
    iov[1].iov_len = BUFFER_SIZE;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return 1;
    }
    
    // 设置服务器地址信息
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[1]));
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("connect");
        return 1;
    }
    totalBytes = readv(sockfd, iov, 2);
    if (totalBytes == -1) {
        perror("readv");
        return 1;
    }
    

    printf("Total bytes read: %ld\n", totalBytes);
    printf("Buffer 1: %.*s\n", (int)iov[0].iov_len, (char*)iov[0].iov_base);
    printf("Buffer 2: %.*s\n", (int)iov[1].iov_len, (char*)iov[1].iov_base);

    return 0;
}
