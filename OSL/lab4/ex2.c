#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    struct stat sb;
    if(argc!=2) {
        fprintf(stderr,"\nusage: %s <file>", argv[0]);
        return 1;
    }
    int ret = stat(argv[1], &sb);
    if(ret) {
        perror("stat");
        return 1;
    }
    printf("\nFile type: ");
    switch(sb.st_mode & S_IFMT) {

        case S_IFBLK:
        printf("\nblock device node");
        break;

        case S_IFCHR:
        printf("\ncharacter device node");
        break;

        case S_IFDIR:
        printf("\ndirectory");
        break;

        case S_IFIFO:
        printf("\nFIFO");
        break;

        case S_IFLNK:
        printf("\nsymbolic link");
        break;

        case S_IFREG:
        printf("\nregular file");
        break;

        case S_IFSOCK:
        printf("\nsocket");
        break;

        default:
        printf("\nunknown");
        break;
    }
    return 0;
}