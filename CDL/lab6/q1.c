#include <stdio.h>
#include <stdlib.h>

int curr=0;
char str[100];

void S();
void T();
void Tprime();

void valid() {
    printf("\nSUCCESS");
    exit(0);
}

void invalid() {
    printf("\nERROR");
    exit(0);
}

void S() {
    if(str[curr]=='a') {
        curr++;
    }
    else if(str[curr]=='>') {
        curr++;
    }
    else if(str[curr]=='(') {
        curr++;
        T();
        if(str[curr]==')') {
            curr++;
        }
        else {
            invalid();
        }
    }
    else {
        invalid();
    }
}

void T() {
    S();
    Tprime();
}

void Tprime() {
    if(str[curr]==',') {
        curr++;
        S();
        Tprime();
    }
}

int main() {
    printf("\nEnter string: ");
    scanf("%s", str);
    S();
    if(str[curr]=='$') {
        valid();
    }
    else {
        invalid();
    }
}