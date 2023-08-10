#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORTNO 8080

void decrypt(char *msg) {
    for(int i=0; msg[i]!='\0'; i++) {
        msg[i]=msg[i]-4;
    }
}

int main() {
    int sockfd, newsockfd, valread;
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    char buffer[1024] = {0};

    sockfd = socket(AF_INET, SOCK_STREAM, 0);  //socket
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORTNO);
    bind(sockfd, (struct sockaddr *)&addr, sizeof(addr));  //bind
    listen(sockfd, 3);  //listen
    printf("Server is listening on PORT: %d", PORTNO);
    newsockfd = accept(sockfd, (struct sockaddr *)&addr, (socklen_t *)&addrlen);  //accept
    valread = read(newsockfd, buffer, 1024);  
    printf("\nEncrypted Message received from client: %s\n", buffer);
    decrypt(buffer);  
    printf("Decrypted Message: %s\n", buffer);
    return 0;
}