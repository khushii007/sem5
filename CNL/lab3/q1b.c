#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Token types
typedef enum {
    SPECIAL_SYMBOL,
    KEYWORD,
    NUMERICAL_CONSTANT,
    STRING_LITERAL,
    IDENTIFIER
} TokenType;

// Token structure
typedef struct {
    int row;
    int col;
    TokenType type;
    char lexeme[100];
} Token;

// Function to check if a character is a special symbol
int is_special_symbol(char c) {
    return (c == ';' || c == ',' || c == '(' || c == ')' || c == '{' || c == '}');
}

// Function to check if a string is a keyword
int is_keyword(const char *str) {
    // Define your list of keywords
    const char *keywords[] = {"int", "float", "if", "else", /* ... */};

    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(keywords[i], str) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to check if a string is a numerical constant
int is_numerical_constant(const char *str) {
    // Implement numerical constant checking
}

// Function to get the next token
Token getNextToken(FILE *input_file, int *row, int *col) {
    Token token;
    char c = fgetc(input_file);
    token.row = *row;
    token.col = *col;

    while (!feof(input_file)) {
        if (c == '\n') {
            (*row)++;
            *col = 0;
        } else {
            (*col)++;
        }

        if (isspace(c)) {
            // Skip whitespace
            c = fgetc(input_file);
            continue;
        } else if (is_special_symbol(c)) {
            // Handle special symbols
            token.type = SPECIAL_SYMBOL;
            token.lexeme[0] = c;
            token.lexeme[1] = '\0';
            return token;
        } else if (isalpha(c)) {
            // Handle keywords and identifiers
            int i = 0;
            while (isalnum(c) || c == '_') {
                token.lexeme[i++] = c;
                c = fgetc(input_file);
            }
            token.lexeme[i] = '\0';

            if (is_keyword(token.lexeme)) {
                token.type = KEYWORD;
            } else {
                token.type = IDENTIFIER;
            }

            return token;
        } else if (isdigit(c)) {
            // Handle numerical constants
            int i = 0;
            while (isdigit(c)) {
                token.lexeme[i++] = c;
                c = fgetc(input_file);
            }
            token.lexeme[i] = '\0';

            if (is_numerical_constant(token.lexeme)) {
                token.type = NUMERICAL_CONSTANT;
            } else {
                // Handle invalid numerical constants
                token.type = -1;
            }

            return token;
        } else {
            // Skip other characters
            c = fgetc(input_file);
        }
    }

    // If no token is found, set the type to -1
    token.type = -1;
    token.lexeme[0] = '\0';
    return token;
}

int main() {
    FILE *input_file = fopen("input.c", "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    int row = 1, col = 1;
    Token token;

    while ((token = getNextToken(input_file, &row, &col)).type != -1) {
        printf("Token at Row %d, Column %d: ", token.row, token.col);
        switch (token.type) {
            case SPECIAL_SYMBOL:
                printf("Special Symbol: %s\n", token.lexeme);
                break;
            case KEYWORD:
                printf("Keyword: %s\n", token.lexeme);
                break;
            case NUMERICAL_CONSTANT:
                printf("Numerical Constant: %s\n", token.lexeme);
                break;
            case STRING_LITERAL:
                printf("String Literal: %s\n", token.lexeme);
                break;
            case IDENTIFIER:
                printf("Identifier: %s\n", token.lexeme);
                break;
            default:
                printf("Unknown Token\n");
        }
    }

    fclose(input_file);
    return 0;
}
