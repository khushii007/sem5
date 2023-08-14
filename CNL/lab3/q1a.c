#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Token types
typedef enum {
    ARITHMETIC_OPERATOR,
    RELATIONAL_OPERATOR,
    LOGICAL_OPERATOR
} TokenType;

// Token structure
typedef struct {
    int row;
    int col;
    TokenType type;
    char lexeme[100];
} Token;

// Function to check if a character is an operator
int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' ||
            c == '=' || c == '<' || c == '>' ||
            c == '&' || c == '|');
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
        } else if (is_operator(c)) {
            // Handle operators
            char lexeme[2];
            lexeme[0] = c;
            lexeme[1] = '\0';

            if ((c == '=' || c == '&' || c == '|') && fgetc(input_file) == c) {
                strcat(lexeme, &c);
                token.type = LOGICAL_OPERATOR;
            } else {
                token.type = (c == '+' || c == '-' || c == '*' || c == '/') ? ARITHMETIC_OPERATOR : RELATIONAL_OPERATOR;
            }

            strcpy(token.lexeme, lexeme);
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
            case ARITHMETIC_OPERATOR:
                printf("Arithmetic Operator: %s\n", token.lexeme);
                break;
            case RELATIONAL_OPERATOR:
                printf("Relational Operator: %s\n", token.lexeme);
                break;
            case LOGICAL_OPERATOR:
                printf("Logical Operator: %s\n", token.lexeme);
                break;
            default:
                printf("Unknown Token\n");
        }
    }

    fclose(input_file);
    return 0;
}
