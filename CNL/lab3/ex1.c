#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fptr;
    char fn1[100], c, buff[100];
    int i;
    printf("\nEnter the input file name: ");
    scanf("%s",fn1);
    fptr = fopen(fn1,"r");
    if(fptr==NULL) {
        printf("\nCannot open file");
        return 1;
    }
    c = fgetc(fptr);
    while(c!=EOF) {
        buff[0]='\0';
        i=0;
        if(c=='=') {
            buff[i++]=c;
            c = fgetc(fptr);
            if(c=='=') {
                buff[i++]=c;
                buff[i]='\0';
                printf("\nRelational operator: %s", buff);
            }
            else {
                buff[i]='\0';
                printf("\nAssignment operator: %s", buff);
            }
        }
        else {
            if(c=='<' || c=='>' || c=='!') {
                buff[i++]=c;
                c = fgetc(fptr);
                if(c=='=') {
                    buff[i++]=c;
                }
                buff[i]='\0';
                printf("\nRelational operator: %s", buff);
            }
            else {
                buff[i]='\0';
            }
        }
        c = fgetc(fptr);
    }
}