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

// sendto and recvfrom function
int main(int argc, char* argv[]) {
    if (argc <= 2) {
        printf("usage: %s ip_address port_number\n", basename(argv[0]));
        return 1;
    }
    const char *ip = argv[1];
    int port = atoi(argv[2]);

    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(port);

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    assert(sock >= 0);

    int ret = bind(sock, (struct sockaddr*)&address, sizeof(address));
    assert(ret != -1);

    struct sockaddr_in client;
    socklen_t cli_addrlen = sizeof(client);

    char buffer[BUFFER_SIZE];
    ssize_t recv_size = recvfrom(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client, &cli_addrlen);
    if (recv_size == -1) {
        perror("recvfrom");
        exit(EXIT_FAILURE);
    }
    buffer[recv_size] = '\0';
    printf("Received from client: %s\n", buffer);

    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client.sin_addr), clientIP, INET_ADDRSTRLEN);
    printf("Client address: %s\n", clientIP);
    printf("Client port: %d\n", ntohs(client.sin_port));

    const char* response = "Hello client";

    ssize_t send_size = sendto(sock, response, strlen(response), 0, (struct sockaddr*)&client, cli_addrlen);
    if (send_size == -1) {
        perror("sendto");
        exit(EXIT_FAILURE);
    }

    close(sock);
    return 0;
}