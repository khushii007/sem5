#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#define PORT 8080


double performOperation(double num1, double num2, char operator) {
    switch (operator) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 != 0) {
                return num1 / num2;
            } else {
                printf("Error: Division by zero\n");
                exit(1);
            }
        default:
            printf("Error: Invalid operator\n");
            exit(1);
    }
}

int main() {
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int valread;
    int serverfd = socket(AF_INET, SOCK_STREAM,0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(serverfd, (struct sockaddr *)&address, sizeof(address));
    listen(serverfd, 3);
    printf("Server listening on port %d...\n", PORT);

    while(1) {
        int newsockfd = accept(serverfd,(struct sockaddr *)&address,(socklen_t *)&addrlen);
        if(fork()==0) {
            double num1, num2, result;
            char operator;
            valread = read(newsockfd, &num1, sizeof(double));
            valread = read(newsockfd, &num2, sizeof(double));
            valread = read(newsockfd, &operator, sizeof(char));
            result = performOperation(num1, num2, operator);
            send(newsockfd, &result, sizeof(double), 0);
            close(newsockfd);
            return 0;
        }
        close(newsockfd);
    }
    return 0;
}