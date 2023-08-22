#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    struct stat sb;
    if(argc!=2) {
        fprintf(stderr, "\nusage: %s <file>", argv[0]);
        return 1;
    }
    //int stat (const char *path, struct stat *buf);On success, zero is returned.  On error, -1 is returned
    int ret = stat(argv[1], &sb);
    if(ret) {
        perror("stat");
        return 1;
    }
    printf("\n%s is %lld bytes", argv[1], sb.st_size);
    return 0;
}