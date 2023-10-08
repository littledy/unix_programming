#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#define BUFFER_SIZE 1024

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sock >= 0);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    const char* message = "Hello server";

    ssize_t send_size = sendto(sock, message, strlen(message), 0, (struct sockaddr*)&address, sizeof(address));
    if (send_size == -1) {
        perror("sendto");
        exit(EXIT_FAILURE);
    }
    
    char buffer[BUFFER_SIZE];
    ssize_t recv_size = recvfrom(sock, buffer, BUFFER_SIZE, 0, NULL, NULL);
    if (recv_size == -1) {
        perror("recv_from");
        exit(EXIT_FAILURE);
    }

    buffer[recv_size] = '\0';
    printf("Received from server: %s\n", buffer);

    close(sock);
    return 0;
}