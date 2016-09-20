
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include "rpn.h"
#include "nextword.h"
#include "stack.h"

double rpn_eval(char * fileName, double x) {
	double a, b, c;

  	FILE *fd;

    // Open file in fileName it.
    	fd = fopen(fileName, "r");
	if(fd == NULL){
		printf("Could not open file %s\n",fileName);
		exit(1);
	}
	stack_clear();
    	char * word;
    	while ((word = nextword(fd))!= NULL) {
		//test
	        //printf("This is word: %s\n",word);
		
		//calculate
		if(!strcmp(word,"+")){
			a = stack_pop();
			b = stack_pop();
			c = a + b;
			stack_push(c);
		}else if(!strcmp(word,"-")){
			a = stack_pop();
			b = stack_pop();
			c = b - a;
			stack_push(c);
		}else if(!strcmp(word,"*")){
			a = stack_pop();
			b = stack_pop();
			c = a * b;
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
		}else if(!strcmp(word,"x")){

			//test
			//printf("this is x: %f\n",x);
			//
			stack_push(x);
		}
		else{
			double n;
			n = atof(word);
			//test
			//printf("the number is: %f\n", n);
			//
			stack_push(n);

			//test
			//stack_print();
		}

	}
    // Check for errors
    //	double check;
//	check = stack[1];
    	if(stack_top() > 1){
		printf("Elements remain in the stack\n");
		exit(1);
	}
    // Return result
    // double result =  stack_pop();
    // return result;
	double result;
	result = stack_pop();
  	return result;
}

