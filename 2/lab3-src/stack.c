
#include <stdio.h>
#include "stack.h"
#include <stdlib.h>

int top=0;
double stack[MAXSTACK];

void stack_clear() 
{
  top = 0;
}

double stack_pop()
{
	// Add implementation here`
	double pop;
	pop = stack[top-1];
	top -- ;
	return pop;
}

void stack_push(double val)
{
	// Add implementation here
	stack[top] = val;
	//printf("%d: %f\n",top,stack[top]);
	top++;
}

void stack_print()
{
	printf("Stack:\n");

	int i = 0;
//	printf("%d: %f\n",top,stack[top]);
	for(i;i<top;i++){
		printf("%d: %f\n",i,stack[i]);
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


