#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#define PORT 8080

void sortArray(int arr[], int size) {
     for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    struct sockaddr_in address;
    int addrlen =sizeof(address);
    int newsockfd, valread;
    int serverfd = socket(AF_INET,SOCK_STREAM,0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(serverfd,(struct sockaddr *)&address,sizeof(address));
    listen(serverfd,5);
    printf("\nServer listening on port %d",PORT);

    while(1) {
        newsockfd = accept(serverfd,(struct sockaddr *)&address, (socklen_t *)&addrlen);
        if (fork()==0) {
            int size;
            int arr[100];
            valread = read(newsockfd, &size, sizeof(int));
            valread = read(newsockfd, arr, size * sizeof(int));
            sortArray(arr,size);
            int pid = getpid();
            send(newsockfd,&pid,sizeof(int),0);
            send(newsockfd,arr,size * sizeof(int),0);
            printf("Sorted array sent back to client with process id: %d",pid);
            //close(newsockfd);
        }
        close(newsockfd);
    }
    return 0;
}