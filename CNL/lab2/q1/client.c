#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 8080

int main() {
    struct sockaddr_in address;
    int size,arr[100], pid, sortArr[100];
    int clientfd = socket(AF_INET,SOCK_STREAM,0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(PORT);
    
    if (connect(clientfd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        printf("\nCLIENT ERROR");
        return 1;
    }
    printf("\nEnter the size of array: ");
    scanf("%d",&size);
    printf("\nEnter the numbers: ");
    for(int i=0; i<size; i++) {
        scanf("%d",&arr[i]);
    }
    send(clientfd,&size,sizeof(int),0);
    send(clientfd,arr,size*sizeof(int),0);
    recv(clientfd,&pid,sizeof(int),0);
    recv(clientfd,sortArr,size*sizeof(int),0);
    printf("Sorted array received from server with PID %d:\n", pid);
    for (int i = 0; i < size; i++) {
        printf("%d ", sortArr[i]);
    }
    close(clientfd);
    return 0;
}