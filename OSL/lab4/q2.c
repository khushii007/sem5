#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

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
    printf("\nDevice node: %ld", sb.st_dev);
    printf("\nInode number: %lu", sb.st_ino);
    printf("\nMode bytes: %d", sb.st_mode);
    printf("\nNumber of hard links pointing at the file: %ld", sb.st_nlink);
    printf("\nUser ID: %d", sb.st_uid);
    printf("\nGroup ID: %d", sb.st_gid);
    printf("\nDevice desciption: %ld", sb.st_rdev);
    printf("\nSize: %ld", sb.st_size);
    printf("\nPreferred block size: %ld", sb.st_blksize);
    printf("\nNumber of filesystem blocks allocated to the file: %ld", sb.st_blocks);
    printf("\nLast file access time: %s", ctime(&sb.st_atime));
    printf("Last file modification time: %s", ctime(&sb.st_mtime));
    printf("Last file change time: %s", ctime(&sb.st_ctime));
    return 0;
}