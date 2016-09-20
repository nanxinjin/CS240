
#include <stdlib.h>
#include "mystring.h"

// Type "man string" to see what every function expects.

int mystrlen(char * s) {
	int i = 0;
	while(s[i] != '\0'){
		i++;
	}
	return i;
}

char * mystrcpy(char * dest, char * src) {
	int i = 0;
	while(src[i] != '\0'){
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return dest;
}

char * mystrcat(char * dest, char * src) {
	int i = 0;
	while(dest[i] != '\0'){
		i++;
	}
	int j = 0;
	while(src[j] != '\0'){
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return dest;
}

int mystrcmp(char * s1, char * s2) {
	while(*s1 == *s2){
		if(*s1 == '\0' | *s2 == '\0')
	 		return 0;

		s1++;
		s2++;
	}
	if((*s1-*s2)>0)
		return 1;
	if((*s1-*s2)<0)
		return -1;
}

char * mystrstr(char * hay, char * needle) {
	int i;
	if(*needle){
		while(*hay){
			for(i = 0;*(hay+i)==*(needle+i);i++){
				if(!*(needle+i+1))
					return (char*)hay;
			}
			hay++;
		}
		return NULL;
	}
	else
		return (char*)hay;
}

char * mystrdup(char * s) {
	int i = 0;
	int j = 0;
	while(*(s+i)!='\0'){
		i++;
	}
	char * size = (char*)malloc(i+1);
	while((size[j]=s[j])!='\0'){
		j++;
	}
	return size;
}

char * mymemcpy(char * dest, char * src, int n)
{
	int i = 0;
	int a = 0;
	for(i;i<=n;i++){
		*(dest+a) = *(src+a);
		a++;
	
	}
	return dest;
}

