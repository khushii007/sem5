#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void printdir(char *dir, int depth) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    if((dp=opendir(dir)) == NULL) {
        printf("cannot open directory: %s\n", dir);
        return;
    }
    chdir(dir);  //changing current directory to the desired directory
    while ((entry = readdir(dp)) != NULL) //loop through each dir in current dir
    {
        lstat(entry->d_name, &statbuf); //retrieve file or directory info n store in statbuf
        if(S_ISDIR(statbuf.st_mode)) //to check if entry is directory or a file
        {
            if(strcmp(".", entry->d_name) == 0 || strcmp("..", entry->d_name) == 0) //if directory is either . or ..
            {continue;
            }
            printf("%*s%s/\n", depth, "", entry->d_name); //proper indentation for printing
            printdir(entry->d_name, depth+4); //recursive exploring sub directories
        }
        
        else //if entry is file
        {
            printf("%*s%s/\n", depth, "", entry->d_name);
        }
    }
    chdir(".."); //going to parent dir
    closedir(dp);
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }
    printdir(argv[1],0);
    return 0;
}