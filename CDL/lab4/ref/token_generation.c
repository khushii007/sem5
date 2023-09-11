#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "token_generation.h"

char *keywords[] = { "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto","if", "int", "long", "register", "return",   "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};

Token token[256];
int ind = 0;
int id_no = 1;
char id_str[20];
int send_count = 0;

int isOtherRelop(char c){
	if(c != '<' && c != '>' && c != '=' && c != '!'){
		return 1;
	}
	return 0;
}

int isOtherLogop(char c){
	if( c != '!' && c != '&' && c != '|'){
		return 1;
	}
	return 0;
}

int isOtherArithmop(char c){
	if(c != '+' && c != '-' && c!= '/' && c != '%' && c != '*'){
		return 1;
	}
	return 0;
}


int isOtherNumerical(char c){
	if(c >= 48 && c <= 57){
		return 0;
	}
	
	return 1;
}

int isStringLiteral(char line[], int i){
	int end_index = i;
	if(line[end_index] == '"'){
		end_index++;
		while(line[end_index] != '"')
			end_index++;
		}
	return end_index;
}

int isKeyword(char *word) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1; 
        }
    }
    return 0; 
}

void makeToken(char type[], char name[], int row_no, int column_no){
	strcpy(token[ind].type, type);
	strcpy(token[ind].name, name);
	token[ind].row_no = row_no;
	token[ind].column_no = column_no;
}

void getRelop(char line[], int row_no){	
	for(int i = 0; i < strlen(line); i++){
		
		i = isStringLiteral(line, i);
		
		if(isOtherRelop(line[i])){
			continue;
		}
		if(line[i] == '!' && line[i + 1] == '='){
			makeToken("!=", "Relop:NE", row_no, i);
			ind++;
			i++;
		}
		if(line[i] == '<' && line[i + 1] == '='){
			makeToken("<=", "Relop:LE", row_no, i);
			ind++;
			i++;
		}
		if(line[i] == '<' && isOtherRelop(line[i + 1])){
			makeToken("<", "Relop:LT", row_no, i);
			ind++;
		}
		if(line[i] == '=' && line[i + 1] == '='){
			makeToken("==", "Relop:EQ", row_no, i);
			ind++;
			i++;
		}
		if(line[i] == '>' && line[i + 1] == '='){
			makeToken(">=", "Relop:GE", row_no, i);
			ind++;
			i++;
		}
		if(line[i] == '>' && isOtherRelop(line[i + 1])){
			makeToken(">", "Relop:GT", row_no, i);
			ind++;
		}
	}
}


void getLogop(char line[], int row_no){
	for(int i = 0; i < strlen(line); i++){
	
		i = isStringLiteral(line, i);
		
		if(isOtherLogop(line[i])){
			continue;
		}
		if(line[i] == '&' && line[i + 1] == '&'){
			makeToken("&&", "LogicalAND", row_no, i);
			ind++;
			i++;
		}
		if(line[i] == '|' && line[i + 1] == '|'){
			makeToken("||", "LogicalOR", row_no, i);
			ind++;
			i++;
		}
		if(line[i] == '!' && isOtherLogop(line[i + 1]) && line[i + 1] != '='){
			makeToken("!", "LogicalNOT", row_no, i);
			ind++;
		}
	}	
}

void getArithmop(char line[], int row_no){
	for(int i = 0; i < strlen(line); i++){
	
		i = isStringLiteral(line, i);
	
		if(isOtherArithmop(line[i])){
			continue;
		}
		if(line[i] == '+' && isOtherArithmop(line[i + 1]) && isOtherArithmop(line[i - 1])){
			makeToken("+", "ADD", row_no, i);
			ind++;
		}
		if(line[i] == '-' && isOtherArithmop(line[i + 1]) && isOtherArithmop(line[i - 1])){
			makeToken("-", "SUB", row_no, i);
			ind++;
		}
		if(line[i] == '/' && isOtherArithmop(line[i + 1])){
			makeToken("/", "DIV", row_no, i);
			ind++;
		}
		if(line[i] == '*' && isOtherArithmop(line[i + 1])){
			makeToken("*", "MUL", row_no, i);
			ind++;
		}
		if(line[i] == '%' && isOtherArithmop(line[i + 1])){
			makeToken("%", "MOD", row_no, i);
			ind++;
		}
	}
}

void getStringLiteral(char line[], int row_no){
	for(int i = 0; i < strlen(line); i++){
		int end_index = isStringLiteral(line, i);
		if(i == end_index)
			continue;
		char literal[256];
		int k = 0;
		for(int j = i; j <=end_index; j++){
			literal[k++] = line[j];
		}
		literal[k] = '\0';
		makeToken(literal,"String_Literal", row_no, i);
		ind++;
		i = end_index;	
	}
}

void getSpecialSymbol(char line[], int row_no){
	for(int i = 0; i < strlen(line); i++){
		i = isStringLiteral(line, i);
		
		if(line[i] == '$'){
			makeToken("$", "SC", row_no, i + 1);
			ind++;
		}
		
		if(line[i] == ','){
			makeToken(",", "SC", row_no, i + 1);
			ind++;
		}
		
		
		if(line[i] == '@'){
			makeToken("@", "SC", row_no, i + 1);
			ind++;
		}
		
		if(line[i] == '['){
			makeToken("[", "SC", row_no, i + 1);
			ind++;
		}
		
		if(line[i] == ']'){
			makeToken("]", "SC", row_no, i + 1);
			ind++;
		}
		
		if(line[i] == '{'){
			makeToken("{", "SC", row_no, i + 1);
			ind++;
		}	
		
		if(line[i] == '}'){
			makeToken("}", "SC", row_no, i + 1);
			ind++;
		}
		
		if(line[i] == '('){
			makeToken("(", "SC", row_no, i + 1);
			ind++;
		}
		
		if(line[i] == ')'){
			makeToken(")", "SC", row_no, i + 1);
			ind++;
		}
	}
}

void getNumericalConstant(char line[], int row_no){
	for(int i = 0; i < strlen(line); i++){
		i = isStringLiteral(line, i);
		
		if(isOtherNumerical(line[i])){
			continue;
		}
		char number[20] = "";
		int j = 0;
		
		if(i >=1 && !((line[i - 1] >= 97 && line[i - 1] <= 122) || (line[i - 1] >= 65 && line[i - 1] <= 90))){
			while(!isOtherNumerical(line[i])){
				number[j++] = line[i++];
			}
			strcat(token[ind].type, "NUM:");
			strcat(token[ind].type, number);
			token[ind].row_no = row_no;
			token[ind].column_no = i;
			ind++;
			continue;
		}
	}
}

void getKeywords(char line[], int row_no){
	int j = 0;
	char new_line[256];
	for(int i = 0; i < strlen(line); i++){
		if(line[i] == '"'){
			i++;
			while(line[i] != '"')
				i++;
			i++;		
		}
		new_line[j++] = line[i];
	}
	char *word = strtok(new_line, " \t\n");
	
	int column = 0;

    	while (word != NULL) {
    		column += strlen(word) + 1;
    		for(int i = 0; i < 32; i++){
    			char* result = strstr(word, keywords[i]);
    			if(result != NULL){
    				int index = result - word;
    				if(index == 0){
    					continue;
    				}
    				if(!((word[index - 1] >= 97 && word[index - 1] <= 122) || (word[index - 1] >= 65 && word[index - 1] <= 90))){
    					index = index + strlen(keywords[i]) - 1;
    					if(index + 1 == strlen(word) || word[index + 1] == '*'){
    						makeToken(keywords[i], "KW", row_no, column);
    						ind++;
    					}
    				}
    			}
    		}
        	if (isKeyword(word)) {
            		makeToken(word,"KW", row_no, column);
			ind++;
        	}
        	word = strtok(NULL, " \t\n");
    	}
}

void getIdentifier(char line[], int row_no){
	for(int i = 0; i < strlen(line); i++){
		i = isStringLiteral(line, i);
		char word[256];
		char name[256] = "id"; 
		int k = 0;
		int start = i;
		if((line[i] >= 97 && line[i] <= 122) || (line[i] >= 65 && line[i] <= 90)){
			i++;
			while(!isOtherNumerical(line[i]) || (line[i] >= 97 && line[i] <= 122) || (line[i] >= 65 && line[i] <= 90)){
				i++;
			}
			
			for(int j = start; j < i; j++){
				word[k++] = line[j]; 		
			}
			word[k] = '\0';
			if(!isKeyword(word)){
				sprintf(id_str, "%d", id_no);
				strcat(name, id_str);
				id_no = id_no + 1;
				makeToken(name, word, row_no, i);
				ind++;
			}
		}
	}
}

int sortTokens(Token token[]){
	for(int i = 0; i < ind - 1; i++){
		for(int j = 0; j < ind - i - 1; j++){
			if(token[j].row_no == token[j + 1].row_no){
				if(token[j].column_no > token[j + 1].column_no){
					Token temp = token[j];
					token[j] = token[j + 1];
					token[j + 1] = temp;
				}
			}
		}
	}
}

Token getNextToken(){
	if(send_count < ind)
		return token[send_count++];		
}

void tokenCreation(){
	char line[256];
	int row = 1;
	FILE* input = fopen("input.c", "r");
	if(input == NULL){
		printf("\nError in opening file");
		exit(1);
	}
	while(fgets(line, 256, input)){
		getRelop(line, row);
		getLogop(line, row);
		getArithmop(line, row);
		getStringLiteral(line, row);
		getNumericalConstant(line, row);
		getSpecialSymbol(line, row);
		getKeywords(line, row);
		getIdentifier(line, row);
		row++;
	}
	sortTokens(token);
}