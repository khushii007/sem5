#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// List of C keywords
const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while"
};

int is_keyword(const char *word) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(keywords[i], word) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    FILE *input_file = fopen("test3.c", "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    char word[100];
    int c;
    int word_idx = 0;

    while ((c = fgetc(input_file)) != EOF) {
        if (isalpha(c)) {
            word[word_idx++] = c;
        } else {
            if (word_idx > 0) {
                word[word_idx] = '\0';
                if (is_keyword(word)) {
                    for (int i = 0; word[i]; i++) {
                        putchar(toupper(word[i]));
                    }
                    putchar('\n');
                }
                word_idx = 0;
            }
        }
    }

    fclose(input_file);
    return 0;
}
