#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 12345
#define MAX_ROWS 10
#define MAX_COLS 10

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[MAX_ROWS][MAX_COLS * sizeof(int)];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind error");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    int matrix[MAX_ROWS][MAX_COLS];
    int row_received = 0;

    while (row_received < MAX_ROWS) {
        recvfrom(sockfd, buffer[row_received], sizeof(buffer[row_received]), 0,
                 (struct sockaddr *)&client_addr, &client_len);

        memcpy(&matrix[row_received], buffer[row_received], sizeof(buffer[row_received]));
        row_received++;

        printf("Received row %d\n", row_received);
    }

    printf("Received the complete matrix:\n");
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    close(sockfd);

    return 0;
}
