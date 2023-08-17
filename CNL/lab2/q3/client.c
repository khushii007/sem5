#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 12345

int main() {
    int client_fd;
    char buffer[1024];
    struct sockaddr_in address;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORT);

    if (connect(client_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        printf("CLIENT ERROR\n");
        exit(1);
    }

    ssize_t size = recv(client_fd, &buffer, sizeof(buffer)-1, 0);
    buffer[size] = '\0';
    printf("%s", buffer);
    close(client_fd);
    return 0;
}