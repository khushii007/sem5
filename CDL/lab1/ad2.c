#include <stdio.h>
#include <string.h>

int main() {
    char fn[25];
    FILE *fptr;
    char line[100], l[100];
    char response;
    printf("\nEnter filename: ");
    scanf("%s", fn);
    fptr = fopen(fn,"r");
    if(fptr == NULL) {
        perror("file");
        return 1;
    }
    while(1) {
        for(int i=0; i<5; i++) {
            if(fgets(line, sizeof(line), fptr)!=NULL) { 
                int size = strlen(line);
                for(int j=0; j<size; j++) {
                    printf("%c", line[j]);
                }  
            }
            else {
                fclose(fptr);
                return 0;
            }
        }
        printf("\nContinue or Quit?");
        scanf(" %c", &response);        //important to add space before taking character inputs
        if(response=='q') {
            fclose(fptr);
            return 0;
        }
    }
}