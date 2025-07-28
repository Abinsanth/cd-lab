%{
#include <stdio.h>

int yylex(void);
int yyerror(const char *s);
int flag = 0;
%}

%token NUMBER
%left '+' '-'
%left '*' '/' '%'
%left '(' ')'

%%

ArithmeticExpression:
      E { printf("\nResult = %d\n", $$); }
;

E : E '+' E    { $$ = $1 + $3; }
  | E '-' E    { $$ = $1 - $3; }
  | E '*' E    { $$ = $1 * $3; }
  | E '/' E    { $$ = $1 / $3; }
  | E '%' E    { $$ = $1 % $3; }
  | '(' E ')'  { $$ = $2; }
  | NUMBER     { $$ = $1; }
;

%%

int yyerror(const char *s) {
    printf("\nEntered arithmetic expression is Invalid: %s\n", s);
    flag = 1;
    return 0;
}

int main() {
    printf("Enter any arithmetic expression with +, -, *, /, %% and ():\n");
    yyparse();
    if (flag == 0)
        printf("Entered arithmetic expression is Valid\n\n");
    return 0;
}
