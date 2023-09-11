#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Token {
    int row;
    int col;
    char type[256];
}Token;

int ind=0;

const char *keywords[] = {
    "auto", "double", "int", "struct",
"break", "else", "long", "switch",
"case", "enum", "register", "typedef",
"char", "extern", "return", "union",
"const", "float", "short", "unsigned",
"continue", "for", "signed", "void",
"default", "goto", "sizeof", "volatile",
"do", "if", "static", "while"
};

const char *SpSymbols[] = {
    "$", ",", ";", "(", ")", "{", "}"
};
 
int isPreprocessorDirective(char *line) {
    if(line[0]=='#') {
        return 1;
    }
    return 0;
}

int isAriOp(char c) {
    if(c=='+' || c=='-' || c=='*' || c=='/') {
        return 1;
    }
    return 0;
}

int isLogOp(char c) {
    if(c=='!' || c=='&' || c=='|') {
        return 1;
    }
    return 0;
}

int isRelOp(char c) {
    if(c=='>' || c=='<' || c=='=') {
        return 1;
    }
    return 0;
}

int isStrLit(char line[], int start_ind) {
    int end_ind = start_ind;
    if(line[start_ind]=='"') {
        end_ind++;
        while(line[end_ind] != '"')
        {
            end_ind++;
        }
    }
    return end_ind;
}

int isKeyword(const char *str) {
    int size = sizeof(keywords) / sizeof(keywords[0]);
    for(int i=0; i<size; i++) {
        if(strcmp(str, keywords[i])==0) {
            return 1;
        }
    }
    return 0;
}

int isSpSymbol(char c) {
    int size = sizeof(SpSymbols) / sizeof(SpSymbols[0]);
    for(int i=0; i<size; i++) {
        if(c == SpSymbols[i][0]) {
            return 1;
        }
    }
    return 0;
}

void createToken(Token token[256], int row, int col, char *str) {
    strcpy(token[ind].type, str);
    token[ind].row = row;
    token[ind].col = col;
    ind++;
}

void getAriOp(char line[], int row, Token token[]) {
    for(int i=0; i<strlen(line); i++) {
        if(isAriOp(line[i]) && !isAriOp(line[i+1]) && !isAriOp(line[i-1]) && (i+1)<strlen(line)) {
            if(line[i]=='+') {
               createToken(token, row, i, "AR: ADD");
            }
            else if(line[i] == '-')
            {
                createToken(token,row,i,"AR: SUB");
            }
            else if(line[i] == '*')
            {
                createToken(token,row,i,"AR: MUL");
            }
            else if(line[i] == '/')
            {
                createToken(token,row,i,"AR: DIV");
            }
        }
        else {
            continue;
        }
    }
}

void getLogOp(char line[], int row, Token token[]) {
    for(int i=0; i<strlen(line); i++) {
        if((i+1)<strlen(line)) {
            if(line[i]=='&' && line[i+1]=='&') {
                createToken(token, row, i, "LOG: AND");
            }
            else if(line[i]=='|' && line[i+1]=='|') {
                createToken(token, row, i, "LOG: OR");
            }
            else if(line[i]=='!' && !isLogOp(line[i+1]) && line[i+1]!='=') {
                createToken(token, row, i, "LOG: NOT");
            }
        }
        else if(!isLogOp(line[i])) {
            continue;
        }
    }
}

void getRelOp(char line[], int row, Token token[]) {
    for(int i=0; i<strlen(line); i++) {
        if((i+1)<strlen(line)) {
            if(line[i]=='>' && !isRelOp(line[i+1])) {
                createToken(token, row, i, "REL: GT");
            }
            else if(line[i]=='<' && !isRelOp(line[i+1])) {
                createToken(token, row, i, "REL: LT");
            }
            /*else if(line[i]=='=' && !isRelOp(line[i+1])) {
                createToken(token, row, i, "ASSIGN: EQ");
            }*/
            else if(line[i]=='>' && line[i+1]=='=') {
                createToken(token, row, i, "REL: GE");
            }
            else if(line[i]=='<' && line[i+1]=='=') {
                createToken(token, row, i, "REL: LE");
            }
            else if(line[i]=='!' && line[i+1]=='=') {
                createToken(token, row, i, "REL: NE");
            }
            else if(line[i]=='=' && line[i+1]=='=') {
                createToken(token, row, i, "REL: EQ");
            }
        }
        else if(!isRelOp(line[i])) {
            continue;
        }
    }
}

void getStrLit(char line[], int row, Token token[]) {
    for(int i=0; i<strlen(line); i++) {
        int start_ind = i;
        int end_ind = isStrLit(line, start_ind);
        if(start_ind != end_ind) {
            char lit[256];
            int k=0;
            for(int j=start_ind; j<=end_ind; j++) {
                lit[k]=line[j];
                k++;
            }
            lit[k] = '\0';
            char str[512] = {"LIT: "};
            strcat (str, lit);
            createToken(token, row, start_ind, str);
            i = end_ind;
        }
        else {
            continue;
        }
    }
}

void getId(char line[], int row, Token token[]) {
    for(int i=0; i<strlen(line); i++) {
        if(isalnum(line[i])) {
            char id[256];
            int k=0;
            for(int j=i; j<strlen(line); j++) {
                while(isalnum(line[j])) {
                    id[k]=line[j];
                    k++;
                    j++;
                }
                id[k]='\0';
                if(!isKeyword(id)) {
                    char str[512] = {"ID: "};
                    strcat (str, id);
                    createToken(token, row, i, str);
                }                
                i = j-1;
            }
        }
        else {
            continue;
        }
    }
}

void getKeyword(char line[], int row, Token token[]) {
    for(int i=0; i<strlen(line); i++) {
        int start_ind =i;
        char str[256];
        int k=0;
        while(isalpha(line[i])) {
            str[k]=line[i];
            k++;
            i++;
        }
        str[k]='\0';
        if(isKeyword(str)) {
            char kw[512] = {"KW: "};
            strcat(kw, str);
            createToken(token, row, start_ind, kw);
        }
    }
}

void getSpSymbols(char line[], int row, Token token[]) {
    for(int i=0; i<strlen(line); i++) {
        if(isSpSymbol(line[i])) {
            char str[256] = "SP SYMBOL: ";
            char sym[2] = {line[i], '\0'};
            strcat(str, sym);
            createToken(token, row, i, str);
        }
        else {
            continue;
        }
    }
}

void sortTokens(Token *token) {
    for(int i=0; i<ind-1; i++) {
        for(int j=0; j<ind-i-1; j++) {
            if(token[j].row == token[j+1].row) {
                if(token[j].col > token[j+1].col) {
                    Token temp = token[j];
                    token[j] = token[j+1];
                    token[j+1] = temp;
                }
            }
        }
    }
}

int main() {
    char filename[25], line[256];
    printf("\nEnter filename: ");
    scanf("%s", filename);
    FILE *fptr1 = fopen(filename, "r");
    if(fptr1==NULL) {
        perror("file");
        return 0;
    }
    FILE *fptr2 = fopen("file2.c", "w");
    if(fptr2==NULL) {
        perror("file");
        return 0;
    }

    while(fgets(line, sizeof(line), fptr1)) {
        if(!isPreprocessorDirective(line)) {
            fputs(line, fptr2);
        }
    }
    fclose(fptr1);
    fclose(fptr2);
    FILE *fptr3 = fopen("file2.c", "r");
    if(fptr3==NULL) {
        perror("file");
        return 0;
    }
    FILE *fptr4 = fopen("file3.c", "w");
    if(fptr4==NULL) {
        perror("file");
        return 0;
    }
    char c = fgetc(fptr3);
    while(c!=EOF) {
        if(c=='/') {
            c = fgetc(fptr3);
            if(c=='/') {
                while(c!='\n') {
                    c = fgetc(fptr3);   //skipping the comment line
                }
            }
            else if(c=='*') {
                c = fgetc(fptr3);
                char prev = c;
                c = fgetc(fptr3);
                while(prev!='*' || c!='/') {    //for skipping multiline comment
                    prev = c;
                    c = fgetc(fptr3);
                }
            }
            else {
                fputc(c, fptr4);
                c = fgetc(fptr3);
            }
        }
        else {
            fputc(c, fptr4);
            c = fgetc(fptr3);
        }
    }
    fclose(fptr3);
    fclose(fptr4);

    FILE *fptr5 = fopen("file3.c", "r");
    if (fptr5 == NULL) {
        perror("file");
        return 1; // Exit with an error code
    }
    int row=1;
    Token token[256];
    while(fgets(line, sizeof(line), fptr5)) {
        //all these functions do not ignore string literals
        getAriOp(line, row, token);
        getLogOp(line, row, token);
        getRelOp(line, row, token);
        getStrLit(line, row, token);
        getId(line, row, token);    //identifier function not working properly for string literals
        getKeyword(line, row, token);
        getSpSymbols(line, row, token);
        row++;
    }
    sortTokens(token);
    for(int i=0; i<ind; i++) {
        printf("\n<%s, %d, %d>", token[i].type, token[i].row, token[i].col);
    }
    fclose(fptr5);
    return 0;
}