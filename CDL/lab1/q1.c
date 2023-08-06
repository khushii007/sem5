#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fptr;
    char filename[100], c;
    int lines=0, characters=0;
    printf("Enter the file name: ");
    scanf("%s",filename);
    fptr = fopen(filename,"r");
    if(fptr == NULL) {
        printf("\nCannot open file %s",filename);
        exit(0);
    }
    c = fgetc(fptr);
    while (c != EOF) {
        if(c == '\n') {
            lines++;
            c = fgetc(fptr);
        }
        else {
            characters++;
            c = fgetc(fptr);
        }
    }
    printf("\nCharacters: %d \nLines: %d", characters, lines);
    fclose(fptr);
    return 0;

}