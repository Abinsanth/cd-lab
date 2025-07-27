%{
#include<stdio.h>
void check();
int p,cb;
%} 

%%
"(" { p++; }
")" { p-- ; }
"{" { cb++; }
"}" { cb--; }
\n { check();}
%%

int main(){
	//printf("Enter the Expression \n");
	yylex();
	return 0;
}
int yywrap(){
	return 1;
}
void check(){
	if(p>0){
		printf("Right pranthesis missing \n");
	}else if(p<0){
		printf("left pranthesis missing \n");
	}else{
		printf("Equal pranthesis \n");
	}
	if(cb>0){
		printf("Right Curly-brace missing \n");
	}else if(cb<0){
		printf("left curly-brace missing \n");
	}else{
		printf("Equal curly-brace \n");
	}
}









