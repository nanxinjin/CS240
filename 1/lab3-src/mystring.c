
#include <stdlib.h>
#include "mystring.h"

int mystrlen(char * s) {
	int n = 0;
	while (*(s + n)!= '\0')
		n++;
	return (n);
}

char * mystrcpy(char * dest, char * src) {
	int i = 0;
	while ((dest[i] = src[i])!= '\0')
	i++;
	return (dest);
}

char * mystrcat(char * dest, char * src) {
	int d = 0;
	int s = 0;
	int checksrc = 0;
	//check the position of '\0' in dest
	while(*(dest + d)!= '\0' )
		d++;
	//check the lenth of src
	while(*(src + s)!= '0')
		s++;
	//copy src to dest from '\0'of dest
	while((dest[d] = src[checksrc])!= '\0') {
		d++;
		checksrc ++;
	}

//	printf("%d",d);
//	printf("%d",s);
//	printf("%d",checksrc);
	return (dest);
}

int mystrcmp(char * s1, char * s2) {
	int a = 0;
	int b = 0;
	while (* (s1 + a) != '\0')
		a++;
	while (* (s2 + b) != '\0')
		b++;
	if (a < b){
		return -1;
	}
	else if (a == b){
		return 0;
	}
	else if (a > b){
		return 1;
	}
}

char * mystrstr(char * hay, char * needle) {
	int a = 0;
	int b = 0;
	char * location;
	while (* (hay + a) != '\0') {
		if (* (hay + a) == * needle) {
			while (*(needle + b) != '\0') {
				if (* (needle + b) == * (hay + a + b)){
					b++;
					if(* (needle + b) == '\0')
						return (hay+a);
				}
					
				else{
					break;
				}
			}
		} 

	a++;
	}
	return NULL;
}

char * mystrdup(char * s) {
	int a = 0;
	int b = 0;
  	char * size;
	while(* (s + a) != '\0')
		a++;
	size = (char *) malloc (a + 1);
	while ((size[b] = s[b]) != '\0')
  		b++;
	return size;
}

char * mymemcpy(char * dest, char * src, int n) {
	int a = 0;
	for (a; a < n ; a++){
		dest[a] = src[a];
	}
	return dest;
}

