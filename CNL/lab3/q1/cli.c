#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 12345
#define SERVER_IP "127.0.0.1"
#define MAX_ROWS 10
#define MAX_COLS 10

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);

    int matrix[MAX_ROWS][MAX_COLS];

    printf("Enter the elements of the matrix (%d rows x %d columns):\n", MAX_ROWS, MAX_COLS);
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            printf("Enter element at position [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    for (int i = 0; i < MAX_ROWS; i++) {
        sendto(sockfd, &matrix[i], sizeof(matrix[i]), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    }

    printf("Sent %d rows of matrix to server.\n", MAX_ROWS);

    close(sockfd);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 12345
#define SERVER_IP "127.0.0.1"
#define MAX_ROWS 10
#define MAX_COLS 10

int main() {
    int sockfd;
    struct sockaddr_in server_addr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    server_addr.sin_port = htons(PORT);

    int matrix[MAX_ROWS][MAX_COLS];

    printf("Enter the elements of the matrix (%d rows x %d columns):\n", MAX_ROWS, MAX_COLS);
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            printf("Enter element at position [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    for (int i = 0; i < MAX_ROWS; i++) {
        sendto(sockfd, &matrix[i], sizeof(matrix[i]), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    }

    printf("Sent %d rows of matrix to server.\n", MAX_ROWS);

    close(sockfd);

    return 0;
}
