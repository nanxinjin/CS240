#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include "rpn.h"
#include "nextword.h"
#include "stack.h"

double rpn_eval(char * fileName, double x) {
	double a,b,c;
	FILE *fd;
	int i = 0;

	//Open file in fileName it.
	fd = fopen(fileName,"r");
	int d;
	//create a char* to store the word from return of nextword()
	char* word;
	while ((word= nextword(fd)) != NULL) {
	
		//Test whether word pick correct
		//printf("%s",word);
	//Check for errors
		if(0){
			printf("Elements remain in the stack");
		}else if(0){
			printf("Stack underflow");
		}
	//define operator
		if(!strcmp(word,"+")){
			a = stack_pop();
			b = stack_pop();
			if(b == 0){
				printf("Stack underflow\n");
				exit(1);
			}
			c = a+b;
			stack_push(c);

		}else if(!strcmp(word,"-")){
			a = stack_pop();
			b = stack_pop();
			c = b-a;
			stack_push(c);
	
		}else if(!strcmp(word,"*")){
			a = stack_pop();
		        b = stack_pop();
			c = a*b;
			stack_push(c);

		}else if(!strcmp(word,"/")){
			a = stack_pop();
			b = stack_pop();
			c = b/a;
			stack_push(c);

		}else if(!strcmp(word,"sin")){
			a = stack_pop();
	                c = sin(a);
			stack_push(c);

		}else if(!strcmp(word,"cos")){
			a = stack_pop();
			c = cos(a);
			stack_push(c);

		}else if(!strcmp(word,"pow")){
			a = stack_pop();
       		         b = stack_pop();
			c = pow(b,a);
			stack_push(c);

		}else if(!strcmp(word,"log")){
			a = stack_pop();
			c = log(a);
			stack_push(c);
		}else if(!strcmp(word,"exp")){
			a = stack_pop();
       		         c = exp(a);
			stack_push(c);
		}
		else if(!strcmp(word,"x")){
			stack_push(x);
	//		printf("this is x: %f",x);
		}
		else{
			//if not operator, covert number from char* to double value,and push them into stack
			double num;
			num = atof(word);
			stack_push(num);
			//test for covert char* to double
		//	printf("this is number %f",num);
		}
	//	stack_print();
}
	
	//Return result
	double result = stack_pop();
	double checkStack = stack_pop();

	//check errors
	if(checkStack != 0){
		printf("Elements remain in the stack\n");
		exit(1);
	}else{
  		return result;
	}
}

