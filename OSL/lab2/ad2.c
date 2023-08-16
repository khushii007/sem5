#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main() {
    DIR *dp;
    char filename[100], response[10];
    struct dirent *entry;
    dp = opendir(".");
    if(!dp) {
        printf("\nCannot open current directory");
        return 1;
    }
    printf("\nEnter the name of the file to remove or 'all' to remove all the files: ");
    scanf("%s", filename);
    if(strcmp(filename, "all") == 0) {
        //dp = opendir(".");
        while((entry = readdir(dp)) != NULL) {
            if(entry->d_type == DT_REG) {
                printf("\nDo you want to remove %s? (y/n): ", entry->d_name);
                scanf("%s", response);
                if(strcmp(response,"y") == 0) {
                    if(remove(entry->d_name) == 0) {
                        printf("\nFile %s is removed.", entry->d_name);
                    }
                    else {
                        printf("\nError removing file %s", entry->d_name);
                    }
                }
            }
        }
        closedir(dp);
    }
    else {
        while((entry = readdir(dp)) != NULL) {
            if(entry->d_type == DT_REG && strcmp(entry->d_name, filename)==0) {
                printf("\nDo you want to remove %s? (y/n): ", entry->d_name);
                scanf("%s", response);
                if(strcmp(response,"y") == 0) {
                    if(remove(entry->d_name) == 0) {
                        printf("\nFile %s is removed.", entry->d_name);
                    }
                    else {
                        printf("\nError removing file %s", entry->d_name);
                    }
                }
                break;
            }
        }
        closedir(dp);
    }
    return 0;
}