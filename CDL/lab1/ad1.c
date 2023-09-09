#include <stdio.h>
#include<string.h>

int main() {
    char fn[25];
    FILE *fptr;
    char line[100];
    int blankLines=0;
    int semicolonLines=0;
    int blankSpaces=0;
    printf("\nEnter filename: ");
    scanf("%s", fn);
    fptr = fopen(fn, "r");
    if(fptr==NULL) {
        perror("file");
        return 1;
    }
    while(fgets(line, sizeof(line), fptr)) {    //iterating through each line and storing in variable array line
        if(line[0]=='\n') {
            blankLines++;
        }
        int size = strlen(line);
        if(line[size-1]==';') {
            semicolonLines++;
        }
        for(int i=0; i<size; i++) {
            if(line[i]==' ') {
                blankSpaces++;
            }
        }
    }
    fclose(fptr);
    printf("Total blank lines: %d\n", blankLines);
    printf("Total lines ending with a semicolon: %d\n", semicolonLines);
    printf("Total blank spaces: %d\n", blankSpaces);
    return 0;
}