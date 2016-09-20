
#include <stdlib.h>
#include "mystring.h"

// Type "man string" to see what every function expects.

int mystrlen(char * s) {
	int i = 0;
	while(*s){
		i++;
		s++;
	}
	return i;
}

char * mystrcpy(char * dest, char * src) {
	int i = 0;
	while(*src){
		*(dest+i) = *src;
		src ++;
		i++;
	}
	dest[i] = '\0';
	return dest;
}

char * mystrcat(char * dest, char * src) {
	int i = 0;
	char *p = dest;
	//find the end of dest
	while(*p){
		i++;
		p++;
	}
	//add src in the end of dest
	while(*src){
		*(dest + i) = *src;
		src++;
		i++;
	}
	dest[i] = '\0';
	return dest;
}

int mystrcmp(char * s1, char * s2) {
	//In this while loop, we assume s1 is not finish.
	while(*s1){
		//find a cahracter in s1 is smaller than s2
		if(*s1 < *s2){
			return -1;
		}//find a character in s1 is larger than s2
		else if(*s1 > *s2){
			return 1;
		}//if s2 gets to the end
		else if(*s2 == '\0'){
			return 1;
		}
		s1 ++;
		s2 ++;
	}
	//s1 gets to the end, if s2 also gets to the end, then they are equal, 
	//if not, then s2 is larger than s1
	if(*s2 == '\0'){
		return 0;
	}else{
		return -1;
	}
}

char * mystrstr(char * hay, char * needle) {
	char * h = hay;
	char * n = needle;

	while(*hay){

		if(*hay == *n){
			//if find the same character, put the pointer on it
			h = hay;
			//chech all charaters in n are the same in hay or not
			while(*n){
				//compare each of character in n
				if(*hay == *n){
					hay ++;
					n++;
				//if onr character in n does not match, then initialize pointer and break loop
				}else{
					n = needle;
					hay = h;
					break;
				}
			}
			//if n goes to the end, it means all characters are same, 
			//then return pointer h we setted before
			if(*n == '\0'){
				return h;
			}
		}
		//does not find the same character, then pointer in hay goes one more
		hay ++;
	}
	//there is no needle in hay
	return NULL;
}

char * mystrdup(char * s) {
	char * save;
	int i = 0;
	int j = mystrlen(s);
	save = (char*)malloc(j*sizeof(char));
	while(*s){
		*(save + i) = *s;
		i++;
		s++;
	}
	save[i] = '\0';

	return save;
}

char * mymemcpy(char * dest, char * src, int n)
{
	char * save = dest;
	int i = 0;
	//copy 
	for(i ; i < n ; i++){
		//if src end before n characters, then break loop
		if(*src == '\0'){
			break;
		}
		*save = *src;
		save++;
		src++;
	}
	*save = '\0';
	return dest;
}


/*test
int main() {
	char a[20] = "abcdefg";
	char* b = (char*) malloc(20);
	mystrcpy(b, a); 
}
*/
