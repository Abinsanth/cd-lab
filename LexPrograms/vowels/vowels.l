%{
#include<stdio.h>
%}

%%
[aeiouAEIOU] { printf("Vowel %s\n",yytext); }
[a-zA-Z] { printf("Consonant %s\n",yytext); }
.|\n ;
%%

int main(){
	yylex();
	return 0;
}
int yywrap(){
	return 1;
}
