#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
typedef struct Token
{
    int row_no;
    int col_no;
    char type[256];
}Token;

int ind = 0;

int ArithOp(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/')
    {
        return 1;
    }
    return 0;
}

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

void createToken(Token token[256],int row_no,int col_no,char *str)
{
    strcpy(token[ind].type,str);
    token[ind].row_no = row_no;
    token[ind].col_no = col_no;
    ind++;
}

void getArithOp(char line[],int row_no,Token token[256])
{
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
                createToken(token,row_no,i,"ADD");
            }
            else if(line[i] == '-')
            {
                createToken(token,row_no,i,"SUB");
            }
            else if(line[i] == '*')
            {
                createToken(token,row_no,i,"MUL");
            }
            else if(line[i] == '/')
            {
                createToken(token,row_no,i,"DIV");
            }
        }
    }
}

void sortTokens(Token *token)
{
    for(int i = 0; i < ind-1; i++)
    {
        for(int j = 0; j < ind-i-1; j++)
        {
            if(token[j].row_no == token[j + 1].row_no)
            {
                if(token[j].col_no > token[j + 1].col_no)
                {
                    Token temp = token[j];
                    token[j] = token[j + 1];
                    token[j + 1] = temp;
                }
            }
        }
    }
}

void getNextToken()
{
    Token token[256];
    char line[256];
    int row_no = 1;
    FILE *fptr1 = fopen("file1.txt","r");
    if(fptr1 == NULL)
    {
        printf("\nERROR:File not opened!");
        exit(0);
    }
    while(fgets(line,256,fptr1))
    {
        getArithOp(line,row_no,token);
        row_no++;
    }
    sortTokens(token);
    for(int i = 0; i < ind; i++)
    {
        printf("\n<%s, %d, %d>",token[i].type,token[i].row_no,token[i].col_no);
    }
    fclose(fptr1);
}
int main()
{
    getNextToken();
    return 0;
}