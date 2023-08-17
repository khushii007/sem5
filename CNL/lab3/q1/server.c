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
    struct sockaddr_in ser_addr, cli_addr;
    int cli_len = sizeof(cli_addr);
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_addr.s_addr = INADDR_ANY;
    ser_addr.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
    printf("\nServer listening on port %d...\n", PORT);

    recvfrom(sockfd, &row, sizeof(int), 0, (struct sockaddr *)&cli_addr, &cli_len);
    recvfrom(sockfd, &col, sizeof(int), 0, (struct sockaddr *)&cli_addr, &cli_len);
    for(int i=0; i<row; i++) {
            recvfrom(sockfd, &matrix[i], sizeof(matrix[i]), 0, (struct sockaddr *)&cli_addr, &cli_len);
            printf("Received row %d\n", i);
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    close(sockfd);
    return 0;

}