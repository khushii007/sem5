#include <stdio.h>
#include <ctype.h>
#include <string.h>

char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};

int isKeyword(const char *word) {
    int size = sizeof(keywords)/sizeof(keywords[0]);
    for(int i=0; i<size; i++) {
        if(strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void toUpper(char *word) {
    for(int i=0; word[i]!='\0'; i++) {
        word[i] = toupper((unsigned char)word[i]);
    }
}

int main() {
    FILE *fptr1, *fptr2;
    char filename[100], c;
    char token[100];
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
    while(c != EOF) {
        int i=0;
        while(isalnum(c)) {
            token[i]=c;
            i++;
            c = fgetc(fptr1);
        }
        token[i]='\0';
        if(isKeyword(token)) {
            char upperToken[100]; // Ensure upperToken has enough space
            if (i < sizeof(upperToken)) {
                strcpy(upperToken, token);
                toUpper(upperToken);
                fputs(upperToken, fptr2);
            } else {
                fputs(token, fptr2); // Token is too long, just write it as is
            }
        }
        else {
            fputs(token, fptr2);
        }
        while(!isalnum(c) && c!=EOF) {
            fputc(c, fptr2);
            c = fgetc(fptr1);
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    printf("\nConverted keywords to uppercase");
    return 0;
}