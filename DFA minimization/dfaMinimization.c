#include <stdio.h>
#include <string.h>

#define MAX 10

int dfa[MAX][MAX], opt_dfa[MAX][MAX];
int n_states, n_symbols;
char finals[MAX], new_finals[MAX];
char equiv[MAX][MAX];

void load_dfa() {
    n_states = 4;
    n_symbols = 2;
    
    dfa[0][0] = 1; dfa[0][1] = 2;
    dfa[1][0] = 1; dfa[1][1] = 3;
    dfa[2][0] = 1; dfa[2][1] = 2;
    dfa[3][0] = 1; dfa[3][1] = 3;
    
    strcpy(finals, "BD");
}

void print_table(int tab[][MAX], int ns, char *f, char *title) {
    int i, j;
    printf("\n%s\n", title);
    printf("State | ");
    for(i = 0; i < n_symbols; i++) printf("%c ", '0'+i);
    printf("\n------+----\n");
    for(i = 0; i < ns; i++) {
        printf("  %c   | ", 'A'+i);
        for(j = 0; j < n_symbols; j++)
            printf("%c ", 'A'+tab[i][j]);
        printf("\n");
    }
    printf("Finals: %s\n", f);
}

int init_partition() {
    int i, j = 0, k = 0;
    for(i = 0; i < n_states; i++) {
        if(strchr(finals, 'A'+i))
            equiv[1][k++] = 'A'+i;
        else
            equiv[0][j++] = 'A'+i;
    }
    equiv[0][j] = equiv[1][k] = '\0';
    return (j > 0 && k > 0) ? 2 : 1;
}

int find_partition(char state) {
    int i;
    for(i = 0; i < MAX; i++)
        if(strchr(equiv[i], state)) return i;
    return -1;
}

int refine_partition(int n_part) {
    int i, j, k, changed = 0;
    char new_equiv[MAX][MAX];
    int new_n = 0;
    
    for(i = 0; i < n_part; i++) {
        if(strlen(equiv[i]) <= 1) {
            strcpy(new_equiv[new_n++], equiv[i]);
            continue;
        }
        
        char temp[MAX][MAX];
        int temp_n = 0;
        
        for(j = 0; equiv[i][j]; j++) {
            int state = equiv[i][j] - 'A';
            char signature[20];
            
            sprintf(signature, "%d%d", 
                find_partition('A'+dfa[state][0]),
                find_partition('A'+dfa[state][1]));
            
            int found = 0;
            for(k = 0; k < temp_n; k++) {
                if(strcmp(temp[k], signature) == 0) {
                    int len = strlen(new_equiv[new_n + k]);
                    new_equiv[new_n + k][len] = equiv[i][j];
                    new_equiv[new_n + k][len+1] = '\0';
                    found = 1;
                    break;
                }
            }
            
            if(!found) {
                strcpy(temp[temp_n], signature);
                new_equiv[new_n + temp_n][0] = equiv[i][j];
                new_equiv[new_n + temp_n][1] = '\0';
                temp_n++;
            }
        }
        
        new_n += temp_n;
        if(temp_n > 1) changed = 1;
    }
    
    for(i = 0; i < new_n; i++)
        strcpy(equiv[i], new_equiv[i]);
    
    return changed ? new_n : n_part;
}

int minimize_dfa() {
    int n_part = init_partition();
    int old_n;
    
    printf("\nInitial partition:\n");
    for(int i = 0; i < n_part; i++)
        printf("P%d: %s\n", i, equiv[i]);
    
    do {
        old_n = n_part;
        n_part = refine_partition(n_part);
        
        if(n_part != old_n) {
            printf("\nRefined partition:\n");
            for(int i = 0; i < n_part; i++)
                printf("P%d: %s\n", i, equiv[i]);
        }
    } while(n_part != old_n);
    
    return n_part;
}

void build_optimized_dfa(int n_opt) {
    int i, j;
    
    for(i = 0; i < n_opt; i++) {
        int rep = equiv[i][0] - 'A';
        for(j = 0; j < n_symbols; j++) {
            int next = dfa[rep][j];
            opt_dfa[i][j] = find_partition('A'+next);
        }
    }
    
    int k = 0;
    for(i = 0; i < n_opt; i++) {
        for(j = 0; equiv[i][j]; j++) {
            if(strchr(finals, equiv[i][j])) {
                new_finals[k++] = 'A'+i;
                break;
            }
        }
    }
    new_finals[k] = '\0';
}

int main() {
    load_dfa();
    print_table(dfa, n_states, finals, "ORIGINAL DFA");
    
    int n_opt = minimize_dfa();
    build_optimized_dfa(n_opt);
    
    print_table(opt_dfa, n_opt, new_finals, "\nMINIMIZED DFA");
    
    printf("\nStates reduced: %d -> %d\n", n_states, n_opt);
    return 0;
}
