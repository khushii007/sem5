#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fptr1, *fptr2, *rfptr;
    char fn1[100];
    char line1[100], line2[100];
    printf("Enter first file name: ");
    scanf("%s",fn1);
    fptr1 = fopen(fn1,"r");
    if(fptr1 == NULL) {
        printf("Cannot open file %s",fn1);
        exit(0);
    }
    printf("Enter second file name: ");
    scanf("%s",fn1);
    fptr2 = fopen(fn1,"r");
    if(fptr2 == NULL) {
        printf("Cannot open file %s",fn1);
        exit(0);
    }
    printf("Enter the resultant file name: ");
    scanf("%s",fn1);
    rfptr = fopen(fn1,"w");

    /*while(fgets(line1, sizeof(line1), fptr1) || fgets(line2, sizeof(line2), fptr2)) {
        if(line1[0]!='\0') {
            fputs(line1, rfptr);
        }
        if(line2[0]!='\0') {
            fputs(line2, rfptr);
        }
    }*/

    while (1) {
        if (fgets(line1, sizeof(line1), fptr1)) {
            fputs(line1, rfptr);
        }
        if (fgets(line2, sizeof(line2), fptr2)) {
            fputs(line2, rfptr);
        }

        // Check if both files are at the end
        if (feof(fptr1) && feof(fptr2)) {
            break;
        }
    }
    
    fclose(fptr1);
    fclose(fptr2);
    fclose(rfptr);
    printf("\nLines merged successfully");
    return 0;
}