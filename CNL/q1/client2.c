#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT 8080

void encrypt(char *msg) {
    for(int i=0; msg[i]!='\0'; i++) {
        msg[i]+=4;
    }
}

int main() {
    int client_fd;
    struct sockaddr_in address;
    char msg[1024];

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    if((connect(client_fd, (struct sockaddr *)&address, sizeof(address))) == -1) {
        printf("\nCLIENT ERROR");
    }
    printf("\nEnter the message to be encrypted: ");
    fgets(msg,1024,stdin);  //stdin to read input from keyboard
    encrypt(msg);
    send(client_fd,msg,strlen(msg),0);
    printf("\nMessage sent to server");
    return 0;
}