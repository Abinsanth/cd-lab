#include<stdio.h>
#include<string.h>

void main(){
    char icode[10][30], str[20], opr[10];
    char regs[4][3] = {"AX", "BX", "CX", "DX"};
    int i=0;
    
    printf("\nEnter the set of intermediate code (terminated by exit):\n");
    do{
        scanf("%s", icode[i]);
    }while(strcmp(icode[i++],"exit")!=0);
    
    printf("\n8086 Target Code \n");
    i=0;
    
    do{
        strcpy(str,icode[i]);
        switch(str[3]){
            case '+': strcpy(opr,"ADD"); break;
            case '-': strcpy(opr,"SUB"); break;
            case '*': strcpy(opr,"MUL"); break;
            case '/': strcpy(opr,"DIV"); break;
        }
        printf("\n\tMOV %s, %c", regs[i%4], str[2]);
        printf("\n\t%s %s, %c", opr, regs[i%4], str[4]);
        printf("\n\tMOV %c, %s\n", str[0], regs[i%4]);
    }while(strcmp(icode[++i],"exit")!=0);
}
