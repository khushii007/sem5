#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#define PORT 8080

int main() {
    int clilen, newsockfd;
    struct sockaddr_in seraddr, cliaddr;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = INADDR_ANY;
    seraddr.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));
    listen(sockfd, 5);
    while (1) {
        char buffer[256];
        printf("\nServer waiting..");
        clilen = sizeof(cliaddr);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, (socklen_t *)&clilen);
        read(newsockfd, buffer, sizeof(buffer));
        if(strcmp(buffer, "stop")==0) {
            close(newsockfd);
            break;
        }
        printf("\nMessage from client: %s", buffer);
        write(newsockfd, buffer, sizeof(buffer));
        close(newsockfd);
    }
    close(sockfd);
    return 0;
}
