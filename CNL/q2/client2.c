#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080

int main() {
    int client_fd;
    struct sockaddr_in address;
    char msg[1024];
    char result[1024]={0};

    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    if((connect(client_fd, (struct sockaddr *)&address, sizeof(address))) == -1) {
        printf("\nCLIENT ERROR");
    }

    while(1) {
        printf("\nEnter a sentence: ");
        fgets(msg,1024,stdin);
        msg[strcspn(msg, "\n")] = '\0';
        send(client_fd,msg,strlen(msg),0);
        if(strcmp(msg,"Stop")==0) {
            printf("\nTerminated");
            break;
        }
        int valread = read(client_fd,result,1024);
        printf("\nResult: %s", result);
    }
    return 0;
}