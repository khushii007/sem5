#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8080

void removeDuplicates(char *sent) {
    char words [100] [100];  //stores unique words
    int wordcount=0;  //count of unique words
    char result[100]="";
    char *token = strtok(sent," ");
    while(token!=NULL) {
        int found = 0;
        for(int i=0; i<wordcount; i++) {
            if(strcmp(words[i], token)==0) {
                found=1;
                break;
            }
        }
        if(!found) {
            strcpy(words[wordcount], token);
            wordcount++;
        }
        token = strtok(NULL," ");
    }
    for(int i=0; i<wordcount; i++) {
        strcat(result, words[i]);
        strcat(result ," ");
    }
    strcpy(sent, result);
}

int main() {
    int serverfd, newsockfd, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024];

    serverfd = socket(AF_INET,SOCK_STREAM,0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(serverfd, (struct sockaddr *)&address, addrlen);
    listen(serverfd,3);
    printf("\nServer listening on port %d",PORT);
    newsockfd = accept(serverfd, (struct sockaddr *)&address, (socklen_t *)&addrlen);

    while(1) {
        valread = read(newsockfd, buffer, 1024);
        if(strcmp(buffer, "Stop") == 0) {
            printf("\nTerminated");
            break;
        }
        removeDuplicates(buffer);
        send(newsockfd, buffer, strlen(buffer), 0);
    }
    return 0;
}