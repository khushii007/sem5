#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <time.h>
#include<string.h>
#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    int serverfd = socket(AF_INET, SOCK_STREAM, 0);
    time_t currentTime;
    char buffer[BUFFER_SIZE];

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(serverfd, (struct sockaddr *)&address, sizeof(address));
    listen(serverfd, 3);
    printf("\nServer listening on port %d...", PORT);

    while(1) {
        int newsockfd = accept(serverfd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
        if(fork()==0) {
            close(serverfd);
            currentTime = time(NULL);
            snprintf(buffer, sizeof(buffer), "\nServer time: %s\nProcess ID: %d", ctime(&currentTime), getpid());
            send(newsockfd, buffer, strlen(buffer), 0);
            close(newsockfd);
            return 0;
        }
        else {
            close(newsockfd);
        }
    }
    close(serverfd);
    return 0;
}