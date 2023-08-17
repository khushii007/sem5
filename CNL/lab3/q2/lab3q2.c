#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
 
#define SERVER_IP "172.217.168.46"  // Google IP address
#define SERVER_PORT 80

int main() {
    struct sockaddr_in address;
    char response[4096];
    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(SERVER_IP);
    address.sin_port = htons(SERVER_PORT);
    if (connect(clientfd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        printf("\nClient connect error");
        return 1;
    }
    char request[] = "GET / HTTP/1.1\r\nHost: www.google.com\r\n\r\n | nc www.google.com 80";
    send(clientfd, request, strlen(request), 0);
    recv(clientfd, response, sizeof(response), 0);
    printf("Received HTTP Response:\n%s\n", response);

    close(clientfd);
    return 0;
}