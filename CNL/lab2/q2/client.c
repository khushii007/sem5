#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main() {
    int client_fd;
    struct sockaddr_in address;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORT);

    if (connect(client_fd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        printf("CLIENT ERROR\n");
        exit(1);
    }

    double num1, num2, result;
    char operator;

    printf("Enter first number: ");
    scanf("%lf", &num1);
    
    printf("Enter operator (+, -, *, /): ");
    scanf(" %c", &operator);
    
    printf("Enter second number: ");
    scanf("%lf", &num2);

    send(client_fd, &num1, sizeof(double), 0);
    send(client_fd, &num2, sizeof(double), 0);
    send(client_fd, &operator, sizeof(char), 0);

    recv(client_fd, &result, sizeof(double), 0);
    
    printf("Result: %.2lf\n", result);

    close(client_fd);
    return 0;
}
