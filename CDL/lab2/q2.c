#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool isPreprocessorDirective(const char *line) {
    return line[0]=='#';
}

int main() {
    FILE *fptr1, *fptr2;
    char filename[100], line[100];
    printf("Input file name: ");
    scanf("%s",filename);
    fptr1 = fopen(filename,"r");
    if(fptr1 == NULL) {
        printf("\nCannot open input file");
        exit(0);
    }
    printf("\nOutput file name: ");
    scanf("%s",filename);
    fptr2 = fopen(filename,"w");
    if(fptr2 == NULL) {
        printf("\nCannot open output file");
        exit(0);
    }
    while(fgets(line, sizeof(line), fptr1) != NULL) {
        if(!isPreprocessorDirective(line)) {
            for(int i=0; line[i] != '\0'; i++) {
                fputc(line[i], fptr2);
            }
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    printf("\nRemoved preprocssor directives successfully");
    return 0;
}