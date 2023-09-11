#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "token_generation.h"

typedef struct ST_row{
	int serial_number;
	char lexeme_name[256];
	char return_type[256];
	char data_type[256];
	char nature[256];
	int no_arguments;
} ST_row;

int no = 0;
ST_row st[1000003];

long long compute_hash(char string[]){
	int p = 31;        // Any prime number
	int m = 1000003;  // Large prime number
	long long hash_value = 0;
	long long power = 1;
	int len = strlen(string);
	
	for(int i = 0; i < len; i++){
		char c = string[i];
		hash_value = (hash_value + (c - 'a'  + 1) * power) % m;
		power = (power * p) % m;
	}
	
	return hash_value;
}

int containsKey(char string[]){
	long long hash_value = compute_hash(string);
	if(strcmp(st[hash_value].lexeme_name, string) == 0){
		return 1;
	}	
	else
		return 0;
}

void display(char string[]){
	long long hash_value = compute_hash(string);
	if(containsKey(string)){
		printf("%d\t%s\t%s\t\t%s         \t%s\t%d\n", st[hash_value].serial_number, st[hash_value].lexeme_name, st[hash_value].return_type, st[hash_value].data_type, st[hash_value].nature, st[hash_value].no_arguments);
	}
	else{
		printf("\nSymbol not present");
	}
}

int main(){
	tokenCreation();
	int total_tokens = ind;
	Token token[ind];
	for(int i = 0; i < total_tokens; i++){
		token[i] = getNextToken();
	}
	Token curr;
	Token prev;
	Token next;
	char type[256];
	for(int i = 0; i < total_tokens; i++){
		curr = token[i];
		if(strstr(curr.type, "id") == NULL){
			continue;
		}
		long long hash_index = compute_hash(curr.name);
		if(containsKey(curr.name)){
			continue;
		}
		st[hash_index].serial_number = no + 1;
		strcpy(st[hash_index].lexeme_name, curr.name);
		int j = i + 1;
			next = token[j];
			if(strcmp(next.type, "(") == 0){
				strcpy(st[hash_index].nature, "Function");
				strcpy(st[hash_index].data_type, "--");
				prev = token[i - 1];
				strcpy(st[hash_index].return_type, prev.type);
				int arguments = 0;
				next = token[++j];
				int flag = 0;
				while(strcmp(next.type, ")") != 0){
					flag = 1;
					if(strcmp(next.type, ",") == 0){
						arguments++;
					}
					next = token[++j];
				}
				if(flag)
					st[hash_index].no_arguments = arguments + 1;
				else
					st[hash_index].no_arguments = arguments;	
			}
			else{
				strcpy(st[hash_index].nature, "Variable");
				st[hash_index].no_arguments = 0;
				strcpy(st[hash_index].return_type, "NULL");
				int k = i - 1;
				while(k >= 0 && strcmp(token[k].name, "KW") != 0){
					k--;
				}
				strcpy(st[hash_index].data_type, token[k].type);
			}
		no++;
	}
	printf("SN\tName\tReturn Type\tData Type\tNature\t\tNumber of Arguments\n");
	display("main");
	display("x");
	display("y");
	display("a");
	display("b");
}