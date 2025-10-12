#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int tmpch = 90;
char str[100], left[15], right[15];

struct exp {
    int pos;
    char op;
} k[15];

int opcount = 0;

void findopr();
void explore();
void fleft(int);
void fright(int);

int main() {
    printf("\t\tINTERMEDIATE CODE GENERATION\n\n");
    printf("Enter the Expression: ");
    scanf("%s", str);
    printf("The intermediate code:\n");
    findopr();
    explore();
    return 0;
}

void findopr() {
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == '/') {
            k[opcount].pos = i;
            k[opcount++].op = '/';
        }
    }
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == '*') {
            k[opcount].pos = i;
            k[opcount++].op = '*';
        }
    }
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == '+') {
            k[opcount].pos = i;
            k[opcount++].op = '+';
        }
    }
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == '-') {
            k[opcount].pos = i;
            k[opcount++].op = '-';
        }
    }
}

void explore() {
    for(int i = 0; i < opcount; i++) {
        fleft(k[i].pos);
        fright(k[i].pos);
        str[k[i].pos] = tmpch--;
        printf("\t%c := %s %c %s\n", str[k[i].pos], left, k[i].op, right);
    }
    
    if(opcount == 0) {
        printf("\t%s := %s\n", str, str);
    } else {
        fright(-1);
        printf("\t%s := %c\n", right, str[k[opcount-1].pos]);
    }
}

void fleft(int x) {
    int w = 0, flag = 0;
    x--;
    
    while(x != -1 && str[x] != '+' && str[x] != '-' && 
          str[x] != '*' && str[x] != '/' && str[x] != '\0') {
        if(str[x] != '$' && flag == 0) {
            left[w++] = str[x];
            left[w] = '\0';
            str[x] = '$';
            flag = 1;
        }
        x--;
    }
}

void fright(int x) {
    int w = 0, flag = 0;
    x++;
    
    while(x != -1 && str[x] != '+' && str[x] != '-' && 
          str[x] != '*' && str[x] != '/' && str[x] != '\0') {
        if(str[x] != '$' && flag == 0) {
            right[w++] = str[x];
            right[w] = '\0';
            str[x] = '$';
            flag = 1;
        }
        x++;
    }
}
