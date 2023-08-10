#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int sockfd, result, n=1;
    struct sockaddr_in address;
    char ch[256], buffer[256];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);  //creating socket
    //naming socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //inet_addr("127.0.0.1");   //write your client's ip
    address.sin_port = htons(8080);
    result = connect(sockfd, (struct sockaddr *)&address, sizeof(address));   //connect socket to server's socket
    if(result==-1) {
        perror("\nCLIENT ERROR");
        exit(1);
    }
    printf("\nENTER STRING\t");
    scanf("%s",ch);
    ch[strlen(ch)]='\0';   //at the end of the string
    write(sockfd, ch, strlen(ch)+1);
    printf("STRING SENT BACK FROM SERVER IS :\n");
    while(n>0) {
        n = read(sockfd, buffer, sizeof(buffer));
        buffer[n]='\0';
        puts(buffer);
    }
    close(sockfd);
    return 0;
}