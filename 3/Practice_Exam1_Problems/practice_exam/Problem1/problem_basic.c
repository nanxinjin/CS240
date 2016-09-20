#include <stdio.h>

// Problem (1/2)
/******************************************************************************
 * TODO: Print each number in succession from low to high
 *       E.g. printRange(1, 4) should print
 *       1, 2, 3, 4
 * 
 * Parameters: low -- the starting range
 *             high -- the ending range
 *
 * Return: void 
 *
 * Return Type: void
 *****************************************************************************/
void printRange(int low, int high) {
	// Write Your Code Here
	int i = low;
	for(i; i <= high; i++){
		printf("%d",i);
		if(i != high){
			printf(", ");
		}
	}
	printf("\n");
}


// Problem ( 2/2 ) 
/******************************************************************************
 * TODO: Print each character of the string 'str' on a seperate line. 
 *       E.g. printString("cat") should print
 *       c
 *       a
 *       t
 * 
 * Parameters: str -- the string you will be printing
 *
 * Return: void 
 *
 * Return Type: void
 *****************************************************************************/
void printString(char * str) {
    // Write Your Code Here
    int i = 0;
    int j = 0;
    char * len = str;
    while(*len){
    	j++;
	len++;
    }
    
    for(i; i < j; i++){
    	printf("%c\n",str[i]);
    }
}
