#include <stdio.h>
#include <stdlib.h>

// Problem ( 1/3 ) 
/******************************************************************************
 * TODO: Compute the length of the string 'str' up to but not including
 * the null terminator. Do not use the built-in string functions or array
 * indexing. Use pointers.
 * 
 * Parameters: str -- This is the string whose length is to be found.
 *
 * Return: The length of the string
 *
 * Return Type: integer
 *****************************************************************************/
int my_str_len(char * str) {
    // Write Your Code Here
    int i = 0;
    while(*str){
    	str++;
	i++;
    }
    return i;
}

// Problem ( 2/3 ) 
/******************************************************************************
 * TODO: Append the src string to the dest string, overwriting the terminating
 * byte at the end of dest, and then add a terminating null byte.
 * Do not use the built-in string functions or array indexing. Use pointers.
 * 
 * Parameters: dest -- This is the pointer to the destination string.
 *             src  -- This is the string to be appended.
 *
 * Return: Return a pointer to the resulting string dest.
 *
 * Return Type: char pointer
 *****************************************************************************/
char * my_str_cat(char * dest, char * src) {
    // Write Your Code Here
    char * d = dest;
    while(*d){
    	d++;
    }
    while(*src){
    	*d = *src;
	src++;
	d++;
    }
    *d = '\0';
    return dest;
}

// Problem ( 3/3 ) 
/******************************************************************************
 * TODO: Copy the string pointed to by src, including the terminating null
 * byte, to the buffer pointed to by dest. Do not use the built-in string
 * functions or array indexing. Use pointers.
 * 
 * Parameters: dest -- This is the pointer to the string where the
 *		       content is to be copied.
 *             src  -- This is the string to be copied.
 *	
 * Return: A pointer to the destination string dest.
 *
 * Return Type: char pointer
 *****************************************************************************/

char * my_str_cpy(char * dest, char * src) {
    // Write Your Code Here
    char * p = dest;
    while(*src){
    	*p = *src;
	p++;
	src++;
    }
    *p = '\0';
    return dest;
}

