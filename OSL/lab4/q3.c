//Write a program to create a new hard link to an existing file and unlink the same. Accept the old path as input and print the newpath.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char newpath[256];
    if(argc!=2) {
        printf("\nusage: %s <file>", argv[0]);
        return 1;
    }
    if(link(argv[1], newpath)) {
        perror("link");
        return 1;
    }
    printf("\nNew hard link created: %s", newpath);
    if(unlink(newpath)) {
        perror("unlink");
        return 1;
    }
    printf("\nUnlinked");
    return 0;
}