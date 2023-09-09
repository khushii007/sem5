#include<stdio.h>

int main() {
    FILE *fptr1, *fptr2;
    char filename[100], c;
    printf("Input file name: ");
    scanf("%s",filename);
    fptr1 = fopen(filename,"r");
    if(fptr1 == NULL) {
        printf("\nCannot open input file");
        return 1;
    }
    printf("\nOutput file name: ");
    scanf("%s",filename);
    fptr2 = fopen(filename,"w");
    if(fptr2 == NULL) {
        printf("\nCannot open output file");
        return 1;
    }
    c = fgetc(fptr1);
    while(c!=EOF) {
        if(c == ' ' || c == '\t') {
            fputc(' ', fptr2);
            c = fgetc(fptr1);
            while(c == ' ' || c == '\t') {
                c = fgetc(fptr1);
            }
        }
        else {
            fputc(c, fptr2);
            c = fgetc(fptr1);
        }   
    }
    fclose(fptr1);
    fclose(fptr2);
    printf("\nBlank spaces and tabs replaced successfully");
    return 0;
}