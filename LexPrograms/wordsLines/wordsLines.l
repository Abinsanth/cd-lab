%{
#include<stdio.h>
int words = 0, lines = 0, chr = 0;
%}

%%
\n { lines++; }
[ \t] { chr+=yyleng; }
[^ \t\n]+ { words++; chr+=yyleng; }
. { chr+=yyleng; }
%%
int main(){
	yylex();
	printf("words\t%d\n",words);
	printf("lines\t%d\n",lines);
	printf("characters\t%d\n",chr);
	return 0;
}

int yywrap(){

	return 1;
}
