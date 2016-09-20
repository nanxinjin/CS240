
#include <stdlib.h>
#include "mystring.h"

int mystrlen(char * s) {
	int i = 0;
	while(*s){
		i++;
		s++;
	}
	return i;
}

char * mystrcpy(char * dest, char * src) {
	char *p = dest;
	while(*src){
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return p;
}

char * mystrcat(char * dest, char * src) {
	char * p  =dest;
	while(*dest){
		dest++;
	}
	while(*src){
		*dest = *src;
		dest ++;
		src++;
	}
	*dest  ='\0';
	return p;
}

int mystrcmp(char * s1, char * s2) {
	char * p = s1;
	char * q = s2;

	while(*s1){
		if(*s1 > *s2){
			return 1;					
		}else if(*s1 < *s2){
			return -1;
		}else{
			s2++;
			s1++;
		}
	}
	if(*s2 == '\0'){
		return 0;
	}else{
		return -1;
	}
}
	



char * mystrstr(char * hay, char * needle) {
	char * h = hay;
	char * n = needle;
	int flag = 0;
	while(*hay){
		if(*hay == *needle){
			h = hay;
			while(*needle){
				if(*needle == *hay){
					needle++;
					hay++;
					flag = 1;
				}else{
					flag = 0;
					hay = h;
					needle = n;
					break;
				}
			}
			if(flag){
				return h;
			}
		}
		hay ++;
	}

}

char * mystrdup(char * s) {
	int i = mystrlen(s);
	char * d = (char*)malloc(sizeof(char)*i);
	d = mystrcpy(d,s);
	
	return d;
}

char * mymemcpy(char * dest, char * src, int n)
{
	char * p = dest;
	int i = mystrlen(src);
	int j = 0;
	for(j;j<n;j++){
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return p; 
}

