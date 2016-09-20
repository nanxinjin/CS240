
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Adds src at the end of dest. Return the value of dest.
char *mystrcat(char * dest, char * src) {
	char *p = dest;
	char *q = src;
	while(*p != '\0'){
		p++;
	}
	while(*q != '\0'){
		*p =*q;
		p++;
		q++;
	}
	*p = '\0';
	return dest;
}


// Return a pointer to the first occurrence of the substring needle in
// the string haystack. 
// Return NULL if the string is not found.
char * mystrstr(char * haystack, char * needle) {
	char *p = haystack;
	char *q = needle;
	int i = 0;
	if(*q){
		while(*p){
			for(i;*(p + i) == *(q + i); i++){
				if(!*(q + i + 1)){
					return (char*)p;
				}
			}
			p++;
		}
		return NULL;
	
	}
	else{
		return (char*)p;
	}
}


// Trims any spaces that are at the beginning or the end of s and returns s.
// Use the same memory passed in s. 
// Example:
// char s1[20];
// strcpy(s1,      hello    );
// strtrim(s1);
// printf(<s1=%s>\n, s1); // it will print <s1=hello>  without the spaces.
char * mystrtrim(char * s) {
	int len = strlen(s);
	char * end = s + len - 1;
	char * begin = s;
	//delete space at the end
	while(*end == ' '){
		*end = '\0';
		end--;
	}
	
	//delete space at the begining
	while(*begin == ' '){
		begin ++;
	}
	while(*begin != '\0'){
		*s = *begin;
		s++;
		begin++;
	}
	*s = '\0';
	return s;
}


// Returns a new string that will substitute the first occurrence of the substring from
//  to the substring to in the string src
// This call will allocate memory for the new string and it will return the new string.
// Example:
// char a[6];
// strcpy(a, apple);
// char * b = strreplace(a, pp, orange);
// printf(<b=%s>\n, b); // It will print <b=aorangele>  
char * mystrreplace( char * src, char * from, char * to)  {
	char * temp = NULL;
	char * newS = NULL;
	char * oldS = NULL;

	if(from == NULL || to == NULL){
		return strdup(src);
	}

	newS = strdup(src);
	int lengthS = strlen(src);
	int lengthF = strlen(from);
	int lengthT = strlen(to);
	//new string length
	int lengthN = lengthS + lengthF + lengthT;
	
	while((temp = strstr(newS,from))){
		oldS = newS;
		newS = malloc(strlen(oldS) - lengthF + lengthT + 1);

	if(newS == NULL){
		free(oldS);
		return NULL;
	}
	memcpy(newS, oldS, temp - oldS);
	memcpy(newS + (temp - oldS), to, lengthT);
	memcpy(newS + (temp - oldS) + lengthT, temp + lengthF, strlen(oldS) - lengthF -
		(temp - oldS));
	memset(newS + strlen(oldS) - lengthF + lengthT, 0,1);
	free(oldS);
	}
	return newS;
}


