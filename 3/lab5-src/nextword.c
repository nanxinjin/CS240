
#include <stdio.h>
#include <stdlib.h>

//
// Separates the file into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength = 0;


// It returns the next word from fd.
// If there are no more more words it returns NULL. 
char * nextword(FILE * fd) {
  	int c;
	// While it is not EOF read char
	while((c = fgetc(fd)) != EOF){
		//ready to return a word before check whether it is a empty word or not.
		if((c == ' ') || (c == '\n') || (c == '\t') || (c == '\r')){
			word[wordLength] = '\0';
			wordLength = 0;

			//check if there are more than one space, skip them
			if(word[0] != '\0'){
				return word;
			}else{
				c++;
			}
		//store non-space char
		}else{
			word[wordLength] = c;
			wordLength ++;
			
		}
	
	}

	/* REQUIREMENT
		While it is not EOF and it is a non-space char
		 store character in word.
		 if char is not in word return word so far.
	 	Return null if there are no more words
	*/
	return NULL;
}

