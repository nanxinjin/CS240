
#include <stdio.h>
#include <stdlib.h>

//
// Separates the file into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;

// It returns the next word from fd.
// If there are no more more words it returns NULL. 
char * nextword(FILE * fd) {
  	int c;
	int i = 0;
	char trash[MAXWORD];
	int j = 0;
	
	// While it is not EOF read char
	while((c=fgetc(fd))!= EOF){
		// While it is not EOF and it is a non-space char
		// store character in word.
			if((c>=48 && c<=57) || c == 42 || c == 43 || c==45 || (c>=97 && c<=122)
			                        || (c>=65 && c<=90) || c==46 || c == 47 || c==39 
						|| c == 44 || c==58 ||c==59||c==63){
				word[i] = c;
				i++;
				wordLength ++;
			}
			else if (c == ' ' || c == '\n'){
				word[i]='\0';
		//check if first char in word is space or '\n',skip return and find next char.
				if(word[0] == '\0'){
					continue;
				}
		// if char is not in word return word so far.
				i = 0;
				return word;
				}
			}
	// Return null if there are no more words
	return NULL;
}

