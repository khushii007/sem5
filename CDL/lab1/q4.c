#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_TABLE_SIZE 100

struct HashEntry {
    char verb[50];
    int hashValue;
    struct hashEntry *next;     //linked list for same hash values
};

struct hashEntry *hashTable[HASH_TABLE_SIZE] = {NULL};      //initialize hash table

int endsWith(const char *str, const char *suffix) {
    int str_len = strlen(str);
    int suffix_len = strlen(suffix);
    if(str_len<suffix_len) {
        return 0;
    }
    if(strcmp(str + str_len - suffix_len, suffix) == 0) {       //to check for suffix part
        return 1;
    }
    else {
        return 0;
    }
}

int hashFun(const char *str) {
    int hash=0;
    while(*str) {       //iterate through each value of str
        hash += *str;       //add ASCII value of each character to hash
        str++;
    }
    return hash % HASH_TABLE_SIZE;
}

void insert(const char *verb) {
    int hashValue = hashFun(verb);      //generate hash value for input verb

    //if verb already exists
    struct HashEntry *current = hashTable[hashValue];       //creating a pointer to the verbs with the same hash values
    while(current!=NULL) {
        if(strcmp(current->verb, verb)==0) {
            printf("\nVerb %s already exists in hash table with hash value %d", verb, current->hashValue);
            return;
        }
        current = current->next;        //iterating through the hashTable's linked list
    }       
    //if verb does not exist
    struct HashEntry *newEntry = (struct HashEntry*)malloc(sizeof(struct HashEntry));
    if(newEntry == NULL) {
        printf("\nMemory allocation error");
        exit(EXIT_FAILURE);
    }
    strncpy(newEntry->verb, verb, sizeof(verb));
    newEntry->hashValue = hashValue;
    newEntry->next = hashTable[hashValue];      //storing the previous hash entry of same value in the hash table's linked list
    hashTable[hashValue] = newEntry;    //new value encountered at top
    printf("\nInserted %s with hash value %d", verb, hashValue);
}

int search(const char *verb) {
    int hashValue = hashFun(verb);
    struct HashEntry *current = hashTable[hashValue];
    while(current!=NULL) {
        if(strcmp(current->verb, verb)==0) {
            return current->hashValue;
        }
        current = current->next;
    }
    return -1;
}

int main() {
    char input[100];
    printf("\nEnter input string: ");
    fgets(input, sizeof(input), stdin);      //for keyboard input
    input[strcspn(input, "\n")] = '\0';     //to remove newline character

    char *token = strtok(input, " ");       //creating token for every word i.e. " " is delimiter
    while(token != NULL) {
            if(endsWith(token,"ing") || endsWith(token,"ed")) {
                insert(token);
            }
            token  = strtok(NULL, " ");     //to continue tokenizing the same string
    }
    int result = search("reading");     //enter any verb to search 
    if(result==-1) {
        printf("\nVerb not found");
    }
    else {
        printf("\nVerb found with hash value: %d", result);
    }
    return 0;
}