%{
#include<stdio.h>
int c=0,v=0;
%}
%%
[aeiouAEIOU]	{ return v++; }
[a-zA-Z]	{ return c++; }
.|\n	;
%%

int main(){
	yylex();
	printf("%d\tVovels\n%d\tConsonants\n",v,c);
	return 0;
}
