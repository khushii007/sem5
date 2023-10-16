#include "lex_analyzer.h"

void program();
void declarations();
void datatype();
void idlist();
void idlistprime();
void statementList();
void statement();
void assign_stat();
void expn();
void eprime();
void simple_exp();
void seprime();
void term();
void tprime();
void factor();
void relop();
void addop();
void mulop();

struct token tkn;
FILE *f1;
char *rel[] = {"==","!=", "<=", ">=", ">", "<"};
char *add[] = {"+", "-"};
char *mul[] = {"*", "/", "%"};

int isrel(char *w) {
	for(int i=0; i<sizeof(rel)/sizeof(char *); i++) {
		if(strcmp(w, rel[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

int isadd(char *w) {
	for(int i=0; i<sizeof(add)/sizeof(char *); i++) {
		if(strcmp(w, add[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

int ismul(char *w) {
	for(int i=0; i<sizeof(mul)/sizeof(char *); i++) {
		if(strcmp(w, mul[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

int main() {
	FILE *fa, *fb;
	char ca, cb;	//to parse through the characters
	fa = fopen("input.c", "r");	//read only
	if(fa==NULL) {
		perror("file");
		exit(0);
	}
	fb = fopen("output.c", "w+");	//read-write
	ca = getc(fa);
	while(ca!=EOF) {

		if(ca == ' ') {		//for removing blank spaces
			putc(ca, fb);
			while(ca == ' ') {
				ca = getc(fa);
			}
		}

		else if(ca == '/') {	//for removing comments
			cb=getc(fa);
			if(cb=='/') {
				while(ca!='\n') {
					ca  = getc(fa);
				}
			}
			else if(cb=='*') {
				do {
					while(ca!='*') {
						ca=getc(fa);
					}
					ca=getc(fa);
				}while(ca!='/');
			}
			else {
				putc(ca, fb);
				putc(cb, fb);
			}
		}

		else {
			putc(ca, fb);
		}

		ca=getc(fa);	//going through each character
	}
	fclose(fa);
	fclose(fb);

	fa=fopen("input.c", "r");
	if(fa==NULL) {
		perror("file");
		return 0;
	}
	fb=fopen("temp.c", "w+");
	ca = getc(fa);
	while(ca!=EOF) {

		if(ca=='#') {		//for removing preprocessor directives
			while(ca!='\n') {	
				ca=getc(fa);
			}
			ca=getc(fa);
		}

		else if(ca=='"') {		//for copying string literals as it is
			putc(ca,fb);
			ca=getc(fa);
			while(ca!='"') {
				putc(ca,fb);
				ca=getc(fa);
			}
		}

		putc(ca, fb);
		ca=fgetc(fa);
	}
	fclose(fa);
	fclose(fb);

	fa=fopen("temp.c","r");
	fb=fopen("output.c". "w");
	ca=getc(fa);
	while(ca!=EOF) {
		putc(ca, fb);
		ca=getc(fa);
	}
	fclose(fa);
	fclose(fb);
	remove("temp.c");
	f1=fopen("output.c", "r");
	if(f1==NULL) {
		perror("file");
		return 0;
	}
	while((tkn=getNextToken(f1)).row!=-1) {		//if no error then execute program()
		if(strcmp(tkn.lexeme, "main") == 0) {
			program();
			break;
		}
	}
	fclose(f1);
}