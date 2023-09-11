#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TableLength 30

// Define an enumeration for token types
enum tokenType {
    EOFILE = -1, LT, LE, GT, GE, EQ, NE
};

// Define a structure for a token
struct token {
    char* lexeme;        // The lexeme (token name)
    int index;           // An index or identifier for the token
    unsigned row, col;   // Row and column information for location
    enum tokenType type; // The token's type, based on the enumeration
};

// Define a structure for an element in the symbol table (a linked list)
struct listElement {
    struct token tok;         // Token information
    struct listElement* next; // Pointer to the next element in the list
};

// An array of pointers to list elements, representing the symbol table
struct listElement* TABLE[TableLength];

// Initialize the symbol table
void initialize() {
    for (int i = 0; i < TableLength; i++) {
        TABLE[i] = NULL;
    }
}

// Function to display the contents of the symbol table
void Display() {
    for (int i = 0; i < TableLength; i++) {
        struct listElement* cur = TABLE[i];
        printf("Bucket %d: ", i);
        while (cur != NULL) {
            printf("(%s, %d) ", cur->tok.lexeme, cur->tok.index);
            cur = cur->next;
        }
        printf("\n");
    }
}

// A simple hash function to calculate the bucket index for a lexeme
int HASH(char* str) {
    int sum = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        sum += str[i];
    }
    return sum % TableLength;
}

// Function to search for a lexeme in the symbol table
int SEARCH(char* lexeme) {
    int val = HASH(lexeme);
    struct listElement* cur = TABLE[val];
    while (cur != NULL) {
        if (strcmp(cur->tok.lexeme, lexeme) == 0) {
            return 1; // Lexeme found in the symbol table
        }
        cur = cur->next;
    }
    return 0; // Lexeme not found
}

// Function to insert a token into the symbol table
void INSERT(struct token tk) {
    if (SEARCH(tk.lexeme) == 1) {
        return; // Lexeme is already present in the symbol table
    }
    int val = HASH(tk.lexeme);
    struct listElement* cur = (struct listElement*)malloc(sizeof(struct listElement));
    cur->tok = tk;
    cur->next = NULL;
    if (TABLE[val] == NULL) {
        TABLE[val] = cur; // No collision, insert at the head of the list
    } else {
        struct listElement* ele = TABLE[val];
        while (ele->next != NULL) {
            ele = ele->next; // Add the element at the end in case of collision
        }
        ele->next = cur;
    }
}

int main() {
    // Initialize the symbol table
    initialize();
    
    // Create some token structures and insert them into the symbol table
    struct token token1 = { "if", 1, 1, 1, EQ };
    struct token token2 = { "else", 2, 2, 3, NE };
    struct token token3 = { "while", 3, 4, 5, LT };
    
    INSERT(token1);
    INSERT(token2);
    INSERT(token3);
    
    // Display the symbol table to check the inserted tokens
    Display();
    
    return 0;
}

/*Here's a step-by-step explanation:

We include necessary header files like <stdio.h>, <stdlib.h>, and <string.h>.

We define a constant TableLength to specify the size of the symbol table.

We define an enumeration enum tokenType to represent different token types.

We define a structure struct token to store token information, including the lexeme (token name), an index, row, column, and the token type.

We define another structure struct listElement to create elements for a linked list. Each element will store a token and have a pointer to the next element in the list.

We declare an array of pointers TABLE to represent the symbol table.

The initialize function sets all elements of the TABLE to NULL, initializing the symbol table.

The Display function displays the contents of the symbol table, showing tokens and their bucket (list) locations.

The HASH function is a simple hash function that calculates a bucket index for a given lexeme based on the sum of its characters' ASCII values.

The SEARCH function searches for a lexeme in the symbol table, returning 1 if found and 0 if not found.

The INSERT function inserts a token into the symbol table after checking if it already exists. It handles collisions by adding tokens to the end of the list in the corresponding bucket.

In the main function:

We initialize the symbol table using initialize.
We create three token structures (token1, token2, token3) and insert them into the symbol table using INSERT.
Finally, we display the symbol table to verify the inserted tokens.
This code provides a basic framework for a symbol table implementation, allowing you to insert tokens, search for tokens, and display the contents of the symbol table.*/