#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <assert.h>

#define BUFFER_SIZE 512

int main(int argc, char* argv[]) {
    if (argc <= 3) {
        printf("usage: %s ip_address port_number send_buffer_size\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in server_addresss;
    bzero(&server_addresss, sizeof(server_addresss));
    server_addresss.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &server_addresss.sin_addr);
    server_addresss.sin_port = htons(port);

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(sock >= 0);

    int sendbufsize = atoi(argv[3]);
    int len = sizeof(sendbufsize);

    setsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbufsize, sizeof(sendbufsize));
    getsockopt(sock, SOL_SOCKET, SO_SNDBUF, &sendbufsize, (socklen_t*)&len);
    printf("The tcp send buffer size after setting is %d\n", sendbufsize);

    if (connect(sock, (struct sockaddr*)&server_addresss, sizeof(server_addresss)) != -1) {
        char buffer[BUFFER_SIZE];
        memset(buffer, 'a', BUFFER_SIZE);
        send(sock, buffer, BUFFER_SIZE, 0);
    }
    close(sock);
    return 0;
}