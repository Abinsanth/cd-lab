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
    printf("\n\t\t E->TE' \n\t\t E'->+TE'|e \n\t\t T->FT' ");
    printf("\n\t\t T'->*FT'|e \n\t\t F->(E)|i");

    printf("\nEnter an arithmetic expression: ");
    scanf("%s", input);   // safer than gets, no overflow

    E();

    if (strlen(input) == i && error == 0)
        printf("\nAccepted..!!!\n");
    else
        printf("\nRejected..!!!\n");

    return 0;
}

void E() {
    T();
    Eprime();
}

void Eprime() {
    if (input[i] == '+') {
        i++;
        T();
        Eprime();
    }
}

void T() {
    F();
    Tprime();
}

void Tprime() {
    if (input[i] == '*') {
        i++;
        F();
        Tprime();
    }
}

void F() {
    if (isalnum(input[i])) {
        while (isalnum(input[i])) 
            i++;
    } else if (input[i] == '(') {
        i++;
        E();
        if (input[i] == ')')
            i++;
        else
            error = 1;
    } else {
        error = 1;
    }
}
