#include<stdio.h>
#include<unistd.h>
//Write a program to create a new soft link to an existing file and unlink the same. Accept the old path as input and print the newpath.
int main(int argc, char *argv[]) {
    char newpath[256];
    if(argc!=2) {
        printf("\nusage: %s <file>", argv[0]);
        return 1;
    }
    if(symlink(argv[1], newpath)) {
        perror("symlink");
        return 1;
    }
    printf("\nNew soft link created: %s", newpath);
    if(unlink(newpath)) {
        perror("unlink");
        return 1;
    }
    printf("\nUnlinked");
    return 0;
}