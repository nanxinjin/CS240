
#include <stdlib.h>
#include "mystring.h"

int mystrlen(char * s) {
	char * p = s;
	int i = 0;
	while(*p != '\0'){
		p++;
		i++;	
	}
	return i;

}

char * mystrcpy(char * dest, char * src) {
	char * p = src;
	char * q = dest;
	while(*p != '\0'){
		*q = *p;
		p++;
		q++;
	}
	*q = '\0';
	return dest;
}

char * mystrcat(char * dest, char * src) {
	char * p = src;
	char * q = dest;
	while (*q != '\0'){
		q++;
	}
	while(*p != '\0'){
		*q = *p;
		p++;
		q++;
	}
	*q = '\0';
	return dest;
}

int mystrcmp(char * s1, char * s2) {
/*	int ascS1 = 0;
	int ascS2 = 0;
	while(*(s1 + ascS1) != '\0'){
		ascS1 ++;
	}

	while(*(s2 + ascS2) != '\0'){
		ascS2 ++;
	}
	if(ascS1 == ascS2){
		return 0;
	}else if(ascS1 < ascS2){
		return -1;
	}else if(ascS1 > ascS2){
		return 1;
	}
	*/
	char * p = s1;
	char * q = s2;
	while(*p != '\0'){
		if(*q == '\0'){
			return 1;
		}
		if(*q > *p){
			return -1;
		}
		if(*p > *q){
			return 1;
		}
		p++;
		q++;
	}
	if(*q != '\0'){
		return -1;
	}
	return 0;
}

char * mystrstr(char * hay, char * needle) {
	char * s1 = hay;
	char * s2 = needle;
	int i =0;
	if(*s2){
		while(*s1){
			for(i;*(s1 + i)== *(s2 + i);i++){
				if(!*(s2 + i + 1)){
					return (char*)s1;
				}
			}
			s1++;
		}
		return NULL;
		}
	else{
		return (char*)s1;
	}
}

char * mystrdup(char * s) {
	char * size = (char*)malloc(mystrlen(s));
	mystrcpy(size,s);
	return size;
}

char * mymemcpy(char * dest, char * src, int n)
{
	int a = 0;
	while(a<n){
		mystrcpy(dest,src);
		a++;
	}
	return dest; 
}

