#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    if(pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t child_pid = fork();
    if(child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(child_pid == 0) {    //child process (consumer)
        int bytes;
        char buffer[100];
        close(pipefd[1]);   //close write end of pipe
        printf("\nConsumer reading from pipe...\n");
        bytes = read(pipefd[0], buffer, sizeof(buffer));
        if(bytes==-1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        printf("\nConsumer: read %d bytes: %s\n", bytes, buffer);
        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    }

    else {  //parent process (producer)
        close(pipefd[0]);   //close read end of pipe
        char msg[] = "message 1";
        printf("\nProducer writing to pipe...\n");
        int bytes = write(pipefd[1], msg, strlen(msg));
        if(bytes==-1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
        printf("\nProducer: wrote %d bytes: %s\n", bytes, msg);
        close(pipefd[1]);
        wait(NULL); //wait for child process
        exit(EXIT_SUCCESS);
    }
}