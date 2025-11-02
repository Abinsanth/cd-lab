%{
#include"y.tab.h"
%}

%%
[0-9]+		return NUM;
[a-zA-Z]	return ID;
[+*/()-=]	return yytext[0];
[\t ]+		;
\n		return 0;
. 		return yytext[0];
%%

int yywrap(){ 
	return 1;
}

