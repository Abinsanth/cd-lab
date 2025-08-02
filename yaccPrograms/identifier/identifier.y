%{
    #include <stdio.h>
    int valid = 1;

    int yylex(void);
    int yyerror(const char *s);
%}

%token letter digit

%%

start : letter s ;

s     : letter s
      | digit s
      | /* empty */ ;

%%

int yyerror(const char *s)
{
    printf("\nIt's not an identifier!\n");
    valid = 0;
    return 0;
}

int main()
{
    printf("Enter a name to test for identifier: ");
    yyparse();

    if (valid)
    {
        printf("\nIt is an identifier!\n");
    }

    return 0;
}
