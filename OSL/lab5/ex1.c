#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int n;
    int fd[2];
    char buf[1025];
    char data[] = "hello.. sample data";
    pipe(fd);
    write(fd[1], &data, strlen(data));
    n=read(fd[0], &buf, 1024);
    if (n >= 0) {
        buf[n]=0;
        printf("read %d bytes from the pipe: \"%s\"\n", n, buf);
    }
    else {
        perror("read");
    }
    return 0;
}