#include <stdio.h>
#include <string.h>
#include <ctype.h>

char input[100];
int i, error;

void E();
void T();
void Eprime();
void Tprime();
void F();

int main() {
    i = 0;
    error = 0;

    printf("\nGrammar without left recursion");
    printf("\n\t E -> T E'");
    printf("\n\t E' -> + T E' | ε");
    printf("\n\t T -> F T'");
    printf("\n\t T' -> * F T' | ε");
    printf("\n\t F -> (E) | i");

    printf("\n\nEnter an arithmetic expression: ");
    scanf("%s", input);

    printf("\n--- Parsing Steps ---\n");

    E();

    if (strlen(input) == i && error == 0)
        printf("\nResult: Accepted\n");
    else
        printf("\nResult: Rejected\n");

    return 0;
}

void E() {
    printf("\nE -> T E' ");
    T();
    Eprime();
}

void Eprime() {
    if (input[i] == '+') {
        printf("\nE' -> + T E' ");
        i++;
        T();
        Eprime();
    } else {
        printf("\nE' -> ε"); 
        
    }
}

void T() {
    printf("\nT -> F T' ");
    F();
    Tprime();
}

void Tprime() {
    if (input[i] == '*') {
        printf("\nT' -> * F T'");
        i++;
        F();
        Tprime();
    } else {
        printf("\nT' -> ε"); 
    }
}

void F() {
    if (isalnum(input[i])) {
        printf("\nF -> id ");
        while (isalnum(input[i])) 
            i++;
    } else if (input[i] == '(') {
        printf("\nF -> (E)");
        i++;
        E();
        if (input[i] == ')') {
            printf("\nMatched ')'");
            i++;
        } else {
            printf("\nError: expected ')' but found '%c'", input[i]);
            error = 1;
        }
    } else {
        printf("\nError: unexpected symbol '%c' in F", input[i]);
        error = 1;
    }
}
