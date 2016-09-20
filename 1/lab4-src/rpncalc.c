
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef struct {
	int nowElement;
	double *content;
}stack;

void stackOpen (stack *a){
	double *newContent;
	newContent = (double*)malloc(sizeof(double));
	a->content = newContent;
	a->nowElement = 0;	
}

void stackSave(stack *a, double e){
	a->content[a->nowElement] = e;
	a->nowElement++;
}

double stackPick(stack *a){
	a->nowElement--;
	return a->content[a->nowElement];
}

int whatCase(char*str){
	if(!strcmp(str,"sin")){
		return 1;
	}else if(!strcmp(str,"cos")){
		return 2;
	}
	else if(!strcmp(str,"pow")){
		return 3;
	}
	else if(!strcmp(str,"log")){
		return 4;
	}
	else if(!strcmp(str,"exp")){
		return 5;
	}
	else if(*str == '+'){
		return 6;
	}
	else if(*str == '-'){
		return 7;
	}
	else if(*str == 'x'){
		return 8;
	}
	else if(*str == '/'){
		return 9;
	}
	
}

int operation(char *str){
	int j;
	int cd = strlen(str);
	for(j = 0;j<cd;j++){
		if(str[j] >= '9' || str[j] <= '0'){
		}
		else{
			if(j = 0 && str[j] == '-'){
			}
			else{
				return 1;
			}
		}
	}
	return 0;
}


main(int argc, char ** argv){
	if(argc < 2){
		printf("Usage: rpncalc op1 op2 ...\n");
	}else{
		double n;
		double n1;
		double n2;
		double n3;
		int result;
		stack * M;
		stackOpen(M);
		char * l = (char*)malloc(4);
		int j;
		for(j = 1; j<argc;j++){
			l = argv[j];
			if(operation(l)){
				n = atof(l);
				stackSave(M,n);
			}else{
				result = whatCase(l);
				switch(result) {
					case 1:
					n1=stackPick(M);
					n3=sin(n1);
					stackSave(M,n3);
					break;

					case 2 :
					n1=stackPick(M);
					n3=cos(n1);
					stackSave(M,n3);
					break;

					case 3:
					n1=stackPick(M);
					n2=stackPick(M);
					n3=pow(n2,n1);
					stackSave(M,n3);
					break;

					case 4:
					n1=stackPick(M);
					n3=log(n1);
					stackSave(M,n3);
					break;

					case 5:
					n1=stackPick(M);
					n3=exp(n1);
					stackSave(M,n3);
					break;

					case 6:
					n1=stackPick(M);
					n2=stackPick(M);
					n3 = n1+n2;
					stackSave(M,n3);
					break;

					case 7:
					n1=stackPick(M);
					n2=stackPick(M);
					n3 = n2-n1;
					stackSave(M,n3);
					break;

					case 8:
					n1=stackPick(M);
					n2=stackPick(M);
					n3 = n1*n2;
					stackSave(M,n3);
					break;

					case 9:
					n1=stackPick(M);
					n2=stackPick(M);
					n3= n2/n1;
					stackSave(M,n3);
					break;

				}
			}
		}
		if(M->nowElement == 1){
			n1=stackPick(M);
			printf("%f\n",n1);
		}
		else if(M->nowElement >1){
			printf("Elements remain in the stack\n");
		
		}
		else{
			printf("Stack underflow\n");
		}
	}

}



