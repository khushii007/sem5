#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
//Write a program to find the inode number of an existing file in a directory. Take the input as a filename and print the inode number of the file.
int main(int argc, char *argv[]) {
    struct stat sb;
    if(argc!=2) {
        printf("\nUsage: %s <file>", argv[0]);
        return 1;
    }
    int ret = stat(argv[1],&sb);
    if(ret) {
        perror("stat");
        return 1;
    }
    printf("\nInode no. of %s is %lu", argv[1], sb.st_ino);
    return 0;
}