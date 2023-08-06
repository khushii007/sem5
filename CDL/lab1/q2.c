#include <stdio.h>
#include <stdlib.h>
int main() {
    FILE *fptr1, *fptr2;
    char filename[100], c;
    int size;
    printf("Enter the source file name: ");
    scanf("%s",filename);
    fptr1 = fopen(filename,"r");
    if(fptr1 == NULL) {
        printf("\nCannot open file %s", filename);
        exit(0);
    }
    printf("\nEnter the destination file name: ");
    scanf("%s", filename);
    fptr2 = fopen(filename, "w");
    fseek(fptr1, 0, SEEK_END);
    size = ftell(fptr1);
    for(int i=0; i<size; i++) {
        fseek(fptr1, size-1-i, SEEK_SET);
        c = fgetc(fptr1);
        fputc(c, fptr2);
    }
    printf("\nSize: %d", size);
    printf("\nContents reversed to %s", filename);
    fclose(fptr1);
    fclose(fptr2);
    return 0;
}