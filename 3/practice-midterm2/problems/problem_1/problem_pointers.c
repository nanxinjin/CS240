#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Problem (1/4)
/******************************************************************************
 * TODO: Print the array.
 *       The format should be (array index)(colon)(array element)(newline) 
 * 
 * Parameters: n -- the number of elements in the array
 *             array -- a double array
 *
 * Return: void 
 *
 * Return Type: void
 *****************************************************************************/
void printArray(int n, double * array) {
// Write Your Code Here
	int i = 0;
	double d = *array;
	for(i;i<n;i++){
		printf("%d:%lf\n",i,d);
		array++;
		d = *array;
	}
}

// Problem (2/4)
/******************************************************************************
 * TODO: Return the minimum element of array 
 * 
 * Parameters: array -- a double array
 *             n -- the number of elements in the array
 *
 * Return: minimum element in array 
 *
 * Return Type: double
 *****************************************************************************/
double minArray(int n, double * array) {
// Write Your Code Here
	int i = 0;
	double a;
	a = *array;
	for(i;i<n;i++){
		if(*array<a){
			a = *array;
		}
		array++;
	}
	return a;
}

// Problem ( 3/4 ) 
/******************************************************************************
 * TODO: Reverse the given string 'str'. 
 * E.g. reverse_str("smile") should return "elims"
 * 
 * Parameters: str -- The given string to be reversed.
 *
 * Return: A pointer to str, str should be reversed 
 *
 * Return Type: char pointer
 *****************************************************************************/
char * reverse_str (char * str ) {
    // Write Your Code Here
    char * s = str;
    int length = strlen(str);
    char * result = (char*)malloc(sizeof(char)*length);
    char * r = result;
    int i = 0;
    while(*s){
    	s++;
    }
    for(i;i<length;i++){
    	s--;
    	*result = *s;
	result++;
    }
    *result = '\0';
    s = str;
    i = 0;
    for(i;i<length;i++){
    	*str = *r;
	str++;
	r++;
    }
    return s;
}

// Problem ( 4/4 ) 
/******************************************************************************
 * TODO: Determine if the string str2 is a permutation of str1. A permutation
 * is the rearranging of characters in a different order. 
 * E.g. the string "act" is a permutation of "cat" 
 *
 * Hint: count the occurences of each letter
 * 
 * Parameters: str1 -- The original string
 *	       str2 -- Determine if this string is a permutation of str1 
 *
 * Return: 1 if str2 is a permutation
 *         0 if str2 is not a permutation
 *
 * Return Type: integer
 *****************************************************************************/
int is_permutation ( char * str1, char * str2 ) {
    // Write Your Code Here
   //char * compare1 = (char*)malloc(sizeof(char)*strlen(str1));
   // char * compare2 = (char*)malloc(sizeof(char)*strlen(str2));
    char * sstr1 = strdup(str1);
    char * sstr2 = strdup(str2);
    char * s1 = sstr1;
    char *compare1 = sstr1;
    char save1;
    while(*s1){
    	while(*compare1){
		if(*s1 > *compare1){
			save1 = *compare1;
		//	printf("%c\n", *compare1);
			*compare1 = *s1;
			*s1 = save1;
		}
		compare1++;
	}
	s1++;
	compare1 = s1;
    }
//	printf("%s\n",sstr1);

    char * s2 = sstr2;
    char * compare2 = sstr2;
    char save2;
    while(*s2){
    	while(*compare2){
		if(*s2 > *compare2){
			save2 = *s2;
			*s2 = *compare2;
			*compare2 = save2;
		}
		compare2++;
	}
	s2++;
	compare2 = s2;
    }
   // printf("%s\n",sstr2);
  int i = 0;
  int length = strlen(str1);
  for(i;i<length;i++){
  	if(*sstr1 != *sstr2){
		return 0;
	}
	sstr1++;
	sstr2++;
  }
  return 1;
}
