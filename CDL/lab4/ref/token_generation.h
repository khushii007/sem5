
#ifndef TOKEN_GENERATION_H
#define TOKEN_GENERATION_H

typedef struct Token {
    int row_no;
    int column_no;
    char type[256];
    char name[256];
} Token;

extern int ind;

void tokenCreation();
Token getNextToken();

#endif