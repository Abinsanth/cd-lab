%{
#include<stdio.h>
int valid = 1;

int yylex(void);
int yyerror (const char *s);

%}

%token NUM ID
%left '+' '-'
%left '*' '/'

%%
S : ID'='E
  | E
  ;
  
E : E'+'E
  | E'-'E
  | E'*'E
  | E'/'E
  | '('E')'
  | NUM
  | ID
  ;
  
%%

int yyerror(const char *s){
	printf("Invalid\n");
	valid  = 0;
	return 1;
}

int main(){
	printf("Enter : ");
	yyparse();
	if(valid) printf("Valid\n");
	return 0;
}
