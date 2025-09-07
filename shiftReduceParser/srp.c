#include <stdio.h>
#include <string.h>

int i = 0, j = 0, k = 0, c = 0;
char a[100], stk[100], act[10], ac[20];

void check();

int main() {
    puts("GRAMMAR is\nE -> E + E\nE -> E * E\nE -> (E)\nE -> id");
    puts("Enter input string (no spaces, e.g., id+id*id): ");
    scanf("%s", a);

    c = strlen(a);
    strcpy(act, "SHIFT->");

    puts("Stack\tInput\tAction");

    i = 0;
    for (j = 0; j < c; j++, i++) {
        if (a[j] == 'i' && j + 1 < c && a[j + 1] == 'd') {
            stk[i] = a[j];
            stk[i + 1] = a[j + 1];
            stk[i + 2] = '\0';
            printf("\n$%s\t%s$\t%sid", stk, a + j + 2, act);
            j++;    // skip the next character of "id"
            check();
            i++;    // stack pointer also increment
        } else {
            stk[i] = a[j];
            stk[i + 1] = '\0';
            printf("\n$%s\t%s$\t%ssymbols", stk, a + j + 1, act);
            check();
        }
    }

    printf("\n");
    return 0;
}

void check() {
    strcpy(ac, "REDUCE TO E");

    // Rule: id -> E
    for (k = 0; k < c; k++) {
        if (stk[k] == 'i' && stk[k + 1] == 'd') {
            stk[k] = 'E';
            stk[k + 1] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a + j + 1, ac);
        }
    }

    // Rule: E + E -> E
    for (k = 0; k < c; k++) {
        if (stk[k] == 'E' && stk[k + 1] == '+' && stk[k + 2] == 'E') {
            stk[k] = 'E';
            stk[k + 1] = '\0';
            stk[k + 2] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a + j + 1, ac);
        }
    }

    // Rule: E * E -> E
    for (k = 0; k < c; k++) {
        if (stk[k] == 'E' && stk[k + 1] == '*' && stk[k + 2] == 'E') {
            stk[k] = 'E';
            stk[k + 1] = '\0';
            stk[k + 2] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a + j + 1, ac);
        }
    }

    // Rule: (E) -> E
    for (k = 0; k < c; k++) {
        if (stk[k] == '(' && stk[k + 1] == 'E' && stk[k + 2] == ')') {
            stk[k] = 'E';
            stk[k + 1] = '\0';
            stk[k + 2] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a + j + 1, ac);
        }
    }
}
