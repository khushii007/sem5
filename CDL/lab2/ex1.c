#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fptr1, *fptr2;
    char filename[100], c;
    printf("Enter the file name: ");
    scanf("%s", filename);
    fptr1 = fopen(filename, "r");
    if (fptr1 == NULL) {
        printf("\nCannot open file %s", filename);
        exit(0);
    }
    printf("\nEnter the output file name: ");
    scanf("%s", filename);
    fptr2 = fopen(filename, "w");
    c = fgetc(fptr1);
    while (c != EOF) {
        if (c == '/') {
            c = fgetc(fptr1);
            if (c == '/') {
                while (c != '\n') {
                    c = fgetc(fptr1);   //skipping the whole comment line
                }
            } else if (c == '*') {      //multiline comment checking
                char prevChar = c;
                c = fgetc(fptr1);
                while (prevChar != '*' || c != '/') {
                    prevChar = c;
                    c = fgetc(fptr1);
                }
                c = fgetc(fptr1);
            } else {    //if not a comment
                fputc('/', fptr2);
                fputc(c, fptr2);
                c = fgetc(fptr1);
            }
        } else {
            fputc(c, fptr2);
            c = fgetc(fptr1);
        }
    }
    printf("\nComments removed successfully");
    fclose(fptr1);
    fclose(fptr2);
    return 0;
}
