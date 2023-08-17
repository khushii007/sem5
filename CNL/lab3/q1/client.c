#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12345

int main() {
    int row, col;
    int matrix[10][10];
    struct sockaddr_in address;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORT);
    printf("\nEnter the row and col size: ");
    scanf("%d %d", &row, &col);
    printf("\nEnter the elements: ");
    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++) {
            printf("\nEnter element at position [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
    sendto(sockfd, &row, sizeof(int), 0, (struct sockaddr *)&address, sizeof(address));
    sendto(sockfd, &col, sizeof(int), 0, (struct sockaddr *)&address, sizeof(address));

    for(int i=0; i<row; i++) {
            sendto(sockfd, &matrix[i], sizeof(matrix[i]), 0, (struct sockaddr *)&address, sizeof(address));
    }
    close(sockfd);
    return 0;
}