//Write a program to print out the complete stat structure of a file.
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    struct stat sb;
    if(argc!=2) {
        printf("\nusage: %s <file>", argv[0]);
        return 1;
    }
    int ret = stat(argv[1], &sb);
    if(ret) {
        perror("stat");
        return 1;
    }
    printf("\nDevice node: %d", sb.st_dev);
    printf("\nInode number: %llu", sb.st_ino);
    printf("\nMode bytes: %d", sb.st_mode);
    printf("\nNumber of hard links pointing at the file: %d", sb.st_nlink);
    printf("\nUser ID: %d", sb.st_uid);
    printf("\nGroup ID: %d", sb.st_gid);
    printf("\nDevice desciption: %d", sb.st_rdev);
    printf("\nSize: %lld", sb.st_size);
    printf("\nPreferred block size: %d", sb.st_blksize);
    printf("\nNumber of filesystem blocks allocated to the file: %lld", sb.st_blocks);
    printf("\nLast file access time: %ld", sb.st_atime);
    printf("\nLast file modification time: %ld", sb.st_mtime);
    printf("\nLast file change time: %ld", sb.st_ctime);
    return 0;
}