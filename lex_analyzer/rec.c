#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int isKeyword(char buffer[]){
    char keywords[32][10] = {
        "void","auto","int","main","if","return","float"
    };
    int i, flag=0;
    for(i=0; i<32; i++) {
        if(strcmp(keywords[i],buffer) == 0){
            flag = 1;
            break;
        }
    }
    return flag;
}

int main() {
    char ch, buffer[15], buf[10]; 
    char operators[] = "+-*/%=";
    char splchar[] = ",;:[]{}()";
    char num[] = "0123456789";
    FILE *fp;
    int i, j=0, k=0;
    fp = fopen("program.txt","r");

    if(fp == NULL) {
        printf("Error opening file\n");
        exit(0);
    }

    while((ch = fgetc(fp)) != EOF ){
        for(i=0; i<strlen(operators); i++){
            if(ch == operators[i])
                printf("%c \tis an operator\n",ch);
        }
        for(i=0; i<strlen(splchar); i++){
            if(ch == splchar[i])
                printf("%c \tis an special character\n",ch);
        }
        
        if(isalpha(ch)){
            buffer[j++] = ch;
        } else if(isdigit){
        } else if((ch == ' ' || ch == '\n') && (j !=0)) {
            buffer[j] = '\0';
            j = 0;
            if(isKeyword(buffer) == 1){
                printf("%s \tis a keyword\n",buffer);
            } else {
                printf("%s \tis identifier\n",buffer);
                printf("%s \tis constant\n",buf);
            }
        }
    }
    fclose(fp);
    return(0);
}

