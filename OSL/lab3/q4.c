#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t child_pid;
    child_pid = fork();
    if(child_pid == -1) {
        printf("\nFork error");
        return 1;
    } 
    else if(child_pid == 0) {
        printf("\n Child process ");
        exit(0);
    }
    else{
        printf("\n Parent process ");
        sleep(1000);
    }
    return 0;
}