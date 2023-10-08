#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <assert.h>
#include <errno.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    if (argc <= 3) {
        printf("usage: %s ip_address port_number send_buffer_size\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    socket(AF_U, SOCK_STREAM, )

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int optval = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    int rcvbufsize = atoi(argv[3]);
    int len = sizeof(rcvbufsize);

    setsockopt(sock, SOL_SOCKET, SO_RCVBUF, &rcvbufsize, sizeof(rcvbufsize));
    getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &rcvbufsize, (socklen_t*)&len);
    printf("The tcp receive buffer size after setting is %d\n", rcvbufsize);

    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    ret = listen(sock, 5);
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t cli_addrlen = sizeof(client);
    int connfd = accept(sock, (struct sockaddr*)&client, &cli_addrlen);
    if (connfd < 0) {
        printf("errno is : %d\n", errno);
    } else {
        char buffer[BUFFER_SIZE];
        memset(buffer, '\0', BUFFER_SIZE);
        while (recv(connfd, buffer, BUFFER_SIZE-1, 0) > 0) {

        }
        close(connfd);
    }

    close(sock);
    return 0;
}