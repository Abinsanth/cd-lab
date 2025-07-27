%{
#include<stdio.h>
%}
%%
abc { printf("ABC"); }
. ECHO;
%%
int main(){
	yylex();
	return 0;
}

