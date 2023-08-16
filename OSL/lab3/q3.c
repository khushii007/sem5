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
        printf("\n Child process");
        printf("\nProcess id: %d", getpid());
        printf("\nParent id: %d", getppid());
        printf("\nChild id: %d", child_pid);
    }
    else {
        printf("\n Parent process");
        printf("\nProcess id: %d", getpid());
        printf("\nParent id: %d", getppid());
        printf("\nChild id: %d", child_pid);
    }
}