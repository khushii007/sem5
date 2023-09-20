#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>

int main() {
    int n;
    char str[256], buffer[256];
    struct sockaddr_in address;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    int result = connect(sockfd, (struct sockaddr *)&address, sizeof(address));
    if(result==-1) {
        perror("\nCLIENT ERROR");
        exit(1);
    }
    printf("\nEnter string: ");
    scanf("%s", str);
    str[strlen(str)]='\0';
    write(sockfd, str, strlen(str)+1);
    read(sockfd, buffer, sizeof(buffer));
    write(sockfd, buffer, sizeof(buffer));
    printf("\nString sent back from server: %s", buffer);
    close(sockfd);
    return 0;
}