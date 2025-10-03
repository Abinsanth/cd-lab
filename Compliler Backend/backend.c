#include <stdio.h>
#include <string.h>

void main()
{
    char icode[10][30], str[20], opr[10];
    int i = 0;

    printf("\n enter the set of intermediate code(formated by exit):\n");
    do {
        scanf("%s", icode[i]);
    } while (strcmp(icode[i++], "exit") != 0);

    printf("\ntarget code generation");
    printf("\n************");
    i = 0;
    do {
        strcpy(str, icode[i]);
        switch (str[3]) {
            case '+':
                strcpy(opr, "ADD");
                break;
            case '-':
                strcpy(opr, "SUB");
                break;
            case '*':
                strcpy(opr, "MUL");
                break;
            case '/':
                strcpy(opr, "DIV");
                break;
        }
        printf("\n\tMOV\t%c,R%d", str[2], i);
        printf("\n\t%s\tR%d,%c", opr, i, str[4]);
        printf("\n\tMOV\t%c,R%d", str[0], i);
    } while (strcmp(icode[++i], "exit") != 0);
}
