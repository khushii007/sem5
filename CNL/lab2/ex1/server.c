#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORTNO 8080

int main() {
    int sockfd, newsockfd, n=1;
    char buf[256];
    struct sockaddr_in seraddr, cliaddr;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    seraddr.sin_family = AF_INET;
    seraddr.sin_addr.s_addr = INADDR_ANY;
    seraddr.sin_port = htons(PORTNO);
    bind(sockfd, (struct sockaddr *)&seraddr, sizeof(seraddr));    
    listen(sockfd, 5);
    while(1) {
        int clilen = sizeof(clilen);
        newsockfd = accept(sockfd, (struct sockaddr *)&cliaddr, (socklen_t *)&clilen);
        if(fork()==0) {
            n = read(newsockfd,buf,sizeof(buf));
            printf("\nMessage from client %s",buf);
            n = write(newsockfd,buf,sizeof(buf));
            close(newsockfd);
        }
        else {
            close(newsockfd);
        }
    }
    return 0;
}