
#include <stdio.h>
#include "stack.h"
#include <stdlib.h>

int top=0;
double stack[MAXSTACK];

void stack_clear() 
{
	int j = 0;
	for(j ; j < MAXSTACK; j++){
		stack[j] = 0;
	}
  	top = 0;
}

double stack_pop()
{
	// Add implementation here`
	
	if(top <= 0){
		printf("Stack underflow\n");
		exit(1);
	}
	double pop;
	top--;
	pop = stack[top];
	
	return pop;
}

void stack_push(double val)
{
	// Add implementation here
	stack[top] = val;
	top ++;
}

void stack_print()
{
	printf("Stack:\n");
	if(top != 0){
		int i = 0;;
		for(i; i < top; i++){
			printf("%d: %lf\n",i,stack[i]);
		}
	}else{
		printf("Stack is empty");
	}
}

int stack_top()
{
  return top;
}

int stack_max()
{
  return MAXSTACK;
}

int stack_is_empty()
{
  return top == 0;
}


