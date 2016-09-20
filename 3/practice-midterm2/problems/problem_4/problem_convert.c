#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_DIGITS 32

// Problem (1/2)
/*****************************************************************************
 * TODO: convert a number from the given base to decimal
 *
 * Parameters: number -- the number you are converting an integer
 *             base   -- the base of the number you are given
 * 
 * Return: The number as an integer
 *
 * Return Type: int
*****************************************************************************/
int toInteger(char * number, int base) {
// Write Your Code Haere
//	printf("%s\n",number);
	int a;
	int sum = 0;
	int i = 0;
//	int a = atoi(number);
//	printf("%d\n",a);
	if(base == 10){
		a = atoi(number);
		return a;
	}else{
		int t = 0;
		for(i;number[i];i++){
			if(number[i] <= '9'){
				t = number[i] - '0';
			}else{
				t = number[i] - 'A' + 10;
			}
			 sum = sum * base + t;
		}
		
	}
	return sum;
}

// Problem (2/2)
/*****************************************************************************
 * TODO: convert a number from the given base to decimal
 *
 * Parameters: number -- the number you are converting a string
 *             base   -- the base you are converting the numebr to
 * 
 * Return: The number as a string in base "base"
 *
 * Return Type: char *
*****************************************************************************/
char * toBase(int number, int base) {
	char * s = (char*)malloc(sizeof(char)*200);
	char * convert = (char*)malloc(sizeof(char)*200);
	char * convertR = convert;
	char * r = s;
	int count = 0;
	int zero = 0;
	int a = 0;
	char c;
	if(base == 10){
		sprintf(s,"%d",number);
		return r;
	}else{
		if(base <= 9){
			count = 0;
			zero = 0;
			while(number != 0){
				a = number%base;
				number /=base;
				c = a + '0';
				*s = c;
				s ++;
				count++;
			}
		}else{
			count = 0;
			zero = 0;
			while(number != 0){
				a = number%base;
				if(a > 9){
					c = a - 10 + 'A';	
				}else{
					c = a + '0';
				}
				number /= base;
				*s = c;
				s++;
				count++;
			}
		}
		for(zero = 0;zero<count;zero++){
			s--;
			*convert = *s;
			convert ++;
		}
		return convertR;
	}
	
}
