#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef  struct Token {
	int row;
	int col;
	char type[256];
}Token;

int ind=0;



int ArithOp(char c) {
	if(c=='+' || c=='-' || c=='*' || c=='/')
		return 1;
	else
		return 0;
}

/*void getArithOp(char line[], int row, Token token[]) {
	for(int i=0; i<strlen(line); i++) {
		if(line[i]=='+') {
			createToken(token, row, i, "ADD");
		}
		else if(line[i]=='-') {
			createToken(token, row, i, "SUB");
		}
		else if(line[i]=='*') {
			createToken(token, row, i, "MUL");
		}
		else if(line[i]=='-') {
			createToken(token, row, i, "DIV");
		}
		else
			continue;
	}
}*/

int isStringLiteral(char line[],int i,int *start_ind)
{
    int end_ind = i;
    if(line[end_ind] == '"')
    {
        (*start_ind) = end_ind;
        end_ind++;
        while(line[end_ind] != '"')
        {
            end_ind++;
        }
    }
    return end_ind;
}

void createToken(Token token[256], int row, int col, char *str) {
	strcpy(token[ind].type, str);
	token[ind].row = row;
	token[ind].row = col;
	ind++;
}

void getArithOp(char line[], int row, Token token[]) {
	 for(int i=0;i<strlen(line);i++)
    {
        int x = 0;
        i = isStringLiteral(line,i,&x);
        if(!ArithOp(line[i]))
            continue;
        if(ArithOp(line[i]) && !ArithOp(line[i+1]) && !ArithOp(line[i-1]) && (i+1)<strlen(line))
        {
            if(line[i] == '+')
            {
                createToken(token,row,i,"ADD");
            }
            else if(line[i] == '-')
            {
                createToken(token,row,i,"SUB");
            }
            else if(line[i] == '*')
            {
                createToken(token,row,i,"MUL");
            }
            else if(line[i] == '/')
            {
                createToken(token,row,i,"DIV");
            }
        }
    }
}

void sortTokens(Token *token) {
	for(int i=0; i<ind-1; i++) {
		for(int j=0; j<ind-i-1; j++) {
			if(token[j].row == token[j+1].row) {
				if(token[j].col > token[j+1].col) {
					Token temp = token[j];
					token[j] = token[j+1];
					token[j+1] = temp;
				}
			}
		}
	}
}

void getNextToken() {
	Token token[256];
	char filename[256];
	char line[256];
	int row=1;
	printf("\nEnter filename: ");
	scanf("%s", filename);
	FILE *fptr = fopen(filename, "r");
	if(fptr==NULL) {
		perror("file");
		exit(0);
	}
	while(fgets(line, 256, fptr)) {
		getArithOp(line, row, token);
		row++;
	}
	sortTokens(token);
	for(int i=0; i<ind; i++) {
		printf("\n<%s, %d, %d>", token[i].type, token[i].row, token[i].col);
	}
	fclose(fptr);
}

int main() {
	getNextToken();
	return 0;
}
