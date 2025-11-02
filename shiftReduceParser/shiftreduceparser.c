#include<stdio.h>
#include<string.h>

int i=0,j=0,k=0,c=0,z=0;
char ac1[10]= "SHIFT -> ", ac2[12] = "REDUCE TO E ", stk[10], a[10];

void check();

void main(){

	printf("GRAMMAR is \n E->E+E \n E->E*E \n E->(E) \n E->id\n");
	
	printf("Enter input string : ");
	scanf("%s",a);
	
	c = strlen(a);
	
	printf("\nstack \t input \t action");
	for(k=0,i=0; j<c; j++,k++,i++){
		
		if(a[j] == 'i' && a[j+1] == 'd'){
			stk[i] = a[j];
			stk[i+1] = a[j+1];
			stk[i+2] = '\0';
			a[j] = ' ';
			a[j+1] = ' ';
			
			printf("\n$%s\t%s$\t%s id", stk, a, ac1);
			check();
		}
		else{
			stk[i] = a[j];
			stk[i+1] = '\0';
			a[j] = ' ';
			printf("\n$%s\t%s$\t%s %c", stk, a, ac1, stk[i]);
			check();
		}
	
	}
	
	if(strlen(stk) == 1)
		printf("\nAccepted\n");
	else
		printf("\nRejected\n");
	
}


void check(){
	
	for(z=0;z<c;z++){
		if(stk[z] == 'i' && stk[z+1] == 'd'){
			stk[z] = 'E';
			stk[z+1] = '\0';
			printf("\n$%s\t%s$\t%s", stk, a, ac2);
			j++;
		}
	}
	
	for(z=0;z<c;z++){
		if(stk[z] == 'E' && stk[z+1] == '*' && stk[z+2] == 'E'){
			stk[z] = 'E';
			stk[z+1] = '\0';
			stk[z+2] = '\0';
			printf("\n$%s\t%s$\t%s", stk, a, ac2);
			i-=2;
		}
	}
	for(z=0;z<c;z++){
		if(stk[z] == 'E' && stk[z+1] == '+' && stk[z+2] == 'E'){
			stk[z] = 'E';
			stk[z+1] = '\0';
			stk[z+2] = '\0';
			printf("\n$%s\t%s$\t%s", stk, a, ac2);
			i-=2;
		}
	}
	for(z=0;z<c;z++){
		if(stk[z] == '(' && stk[z+1] == 'E' && stk[z+2] == ')'){
			stk[z] = 'E';
			stk[z+1] = '\0';
			stk[z+2] = '\0';
			printf("\n$%s\t%s$\t%s", stk, a, ac2);
			i-=2;
		}
	}

}
