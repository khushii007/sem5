#include <stdio.h>
//#include <stdlib.h>
#include <unistd.h>
//+#include <string.h>

int main(int argc, char *argv[]) {
    char newpath[256];
    if(argc!=2) {
        printf("\nusage: %s <file>", argv[0]);
        return 1;
    }
    printf("\nEnter the newpath: ");
    scanf("%s", newpath);
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