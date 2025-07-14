#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char buffer[]) {
    char keywords[32][10] = {
        "auto", "break", "case", "char", "const", "continue", "default",
        "do", "double", "else", "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return", "short", "signed",
        "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };

    for (int i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char ch, buffer[15], buf[15];
    char operators[] = "+-*/%=";
    char specialch[] = ":;[]{}()";
    FILE *fp;
    int i, j = 0, k = 0;

    fp = fopen("program.txt", "r");
    if (fp == NULL) {
        printf("Error while opening the file\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        // Collect letters into buffer
        if (isalpha(ch)) {
            buffer[j++] = ch;
        }
        // Collect digits and dot into buf
        else if (isdigit(ch) || ch == '.') {
            buf[k++] = ch;
        }
        // On delimiter or whitespace, flush buffers
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
            // Operators
            for (i = 0; i < strlen(operators); i++) {
                if (ch == operators[i]) {
                    printf("%c\toperator\n", ch);
                    break;
                }
            }
            // Special characters
            for (i = 0; i < strlen(specialch); i++) {
                if (ch == specialch[i]) {
                    printf("%c\tspecial character\n", ch);
                    break;
                }
            }
        }
    }

    // Final flush at EOF
    if (j != 0) {
        buffer[j] = '\0';
        if (isKeyword(buffer))
            printf("%s\tkeyword\n", buffer);
        else
            printf("%s\tidentifier\n", buffer);
    }
    if (k != 0) {
        buf[k] = '\0';
        printf("%s\tconstant\n", buf);
    }

    fclose(fp);
    return 0;
}

