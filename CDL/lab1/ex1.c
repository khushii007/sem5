#include<stdio.h>
#include<stdlib.h>
int main() {
    char filename1[25], filename2[25], c;
    FILE *fptr1, *fptr2;
    printf("\nEnter filename: ");
    scanf("%s", filename1);
    fptr1 = fopen(filename1,"r");
    if(fptr1 == NULL) {
        perror("file");
        return 1;
    }
    printf("\nEnter filename for writing: ");
    scanf("%s", filename2);
    fptr2 = fopen(filename2,"w");
    c = fgetc(fptr1);
    while(c!=EOF) {
        fputc(c, fptr2);
        c = fgetc(fptr1);
    }
    printf("\nContents copied");
    fclose(fptr1);
    fclose(fptr2);
    return 0;
}