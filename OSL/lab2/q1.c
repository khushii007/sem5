#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
//#include <pwd.h>

void permissions(mode_t mode) {
    putchar((S_ISDIR(mode)) ? 'd' : '-');
    printf("USER:");
    putchar((mode & S_IRUSR) ? 'r' : '-');
    putchar((mode & S_IWUSR) ? 'w' : '-');
    putchar((mode & S_IXUSR) ? 'x' : '-');
    printf(" GROUP:");
    putchar((mode & S_IRGRP) ? 'r' : '-');
    putchar((mode & S_IWGRP) ? 'w' : '-');
    putchar((mode & S_IXGRP) ? 'x' : '-');
    printf(" OTHERS:");
    putchar((mode & S_IROTH) ? 'r' : '-');
    putchar((mode & S_IWOTH) ? 'w' : '-');
    putchar((mode & S_IXOTH) ? 'x' : '-');
}

void ls_l(char *dir) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    char path[512];

    if((dp = opendir(dir)) == NULL) {
        printf("\nCannot open directory %s", dir);
        return;
    }
    while((entry = readdir(dp)) != NULL) {
        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);
        if(stat(path, &statbuf) == -1) {
            printf("\nstat error");
            continue;
        }
        permissions(statbuf.st_mode);
        printf("    %s\n",entry->d_name);
    }   
    closedir(dp);
}

int main() {
    ls_l(".");  //for current directory
    return 0;
}