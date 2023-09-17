#include <stdio.h>
#include <stdlib.h>

int curr=0;
char str[100];

void S();
void A();
void Aprime();
void B();

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
        A();
        if(str[curr]=='c') {
            curr++;
            B();
        }
        else
            invalid();
        if(str[curr]=='e') {
            curr++;
        }
    }
    else
        invalid();
}

void A() {
    if(str[curr]=='b') {
        curr++;
        Aprime();
    }
    else 
        invalid();
}

void Aprime() {
    if(str[curr]=='b') {
        curr++;
        Aprime();
    }
}

void B() {
    if(str[curr]=='d') {
        curr++;
    }
    else
        invalid();
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