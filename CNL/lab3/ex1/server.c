#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include<netinet/in.h> 
#include<arpa/inet.h> 
#include<unistd.h>
#define PORT 8080

int main() {
    char buf[25];
    struct sockaddr_in sadd, cadd;
    int cliLen = sizeof(cadd);
    int sd = socket(AF_INET, SOCK_DGRAM, 0);
    sadd.sin_family = AF_INET;
    sadd.sin_addr.s_addr = INADDR_ANY;
    sadd.sin_port = htons(PORT);
    int result = bind(sd, (struct sockaddr *)&sadd, sizeof(sadd));
    int m = recvfrom(sd, buf, sizeof(buf), 0, (struct sockaddr *)&cadd, &cliLen);
    printf("the server send is\n");
    puts(buf);
    int n = sendto(sd, buf, sizeof(buf), 0, (struct sockaddr *)&cadd, cliLen);
    return 0;
}