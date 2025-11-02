#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char *w){
    char *kw[]={"int","float","char","if","else","while","for","return","void","double","main"};
    for(int i=0;i<11;i++) if(!strcmp(kw[i],w)) return 1;
    return 0;
}

int main() {
    char ch, buffer[15], buf[15];
    FILE *fp;
    int i, j = 0, k = 0;

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("Error while opening the file\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {

        if (isalpha(ch)) {
            buffer[j++] = ch;
        }else if (isdigit(ch) || ch == '.') {
            buf[k++] = ch;
        }

        else {
            if (j != 0) {
                buffer[j] = '\0';
                if (isKeyword(buffer))
                    printf("%s\tkeyword\n", buffer);
                else
                    printf("%s\tidentifier\n", buffer);
                j = 0;
            }
            if (k != 0) {
                buf[k] = '\0';
                printf("%s\tconstant\n", buf);
                k = 0;
            }

            if (isspace(ch)) {
                continue;
            }

            if(strchr("=+-*/",ch)) printf("%c\toperator\n", ch);
            else if(strchr(";,(){}",ch)) printf("%c\tspecial character\n", ch);
            
        }
    }
    fclose(fp);
    return 0;
}
