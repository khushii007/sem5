#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t child_pid;
    int status;
    child_pid = fork();

    if (child_pid == -1) {
        printf("\nFork error");
        return 1;
    }
    else if(child_pid == 0) {
        execlp("/home/student/Desktop/210905156_OSL/lab3/q1","q1",NULL);
    }
    else {
        wait(NULL);
        printf("\nParent: Child complete");
        return 0;
    }
}