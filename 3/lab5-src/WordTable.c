
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "WordTable.h"

// Initializes a word table
void wtable_init(WordTable * wtable)
{
	// Allocate and initialize space for the table
	wtable->nWords = 0;
	wtable->maxWords = 10;
	wtable->wordArray = (WordInfo *) malloc(wtable->maxWords * sizeof(WordInfo));
	for (int i = 0; i < wtable->maxWords; i++) {
		llist_init(&wtable->wordArray[i].positions);
	}
}

// Add word to the tableand position. Position is added to the corresponding linked list.
void wtable_add(WordTable * wtable, char * word, int position)
{
	// Find first word if it exists
	for (int i = 0; i < wtable->nWords; i++) {
		if ( strcmp(wtable->wordArray[i].word, word)== 0 ) {
			// Found word. Add position in the list of positions
			llist_insert_last(&wtable->wordArray[i].positions, position);
			return;
		}
		
	}

	// Word not found.

	// Make sure that the array has space.
	// Expand the wordArray here.
	if(wtable->nWords == wtable->maxWords){
		wtable->wordArray = (WordInfo*)realloc(wtable->wordArray,sizeof(WordInfo)*(wtable->maxWords*2));
		wtable->maxWords = wtable->maxWords * 2;
	}
	// Add new word and position
	wtable->wordArray[wtable->nWords].word = strdup(word);
	llist_insert_last(&wtable->wordArray[wtable->nWords].positions, position);
	wtable->nWords++;
}

// Print contents of the table.
void wtable_print(WordTable * wtable, FILE * fd)
{
	fprintf(fd, "------- WORD TABLE -------\n");

	// Print words
	for (int i = 0; i < wtable->nWords; i++) {
		fprintf(fd, "%d: %s: ", i, wtable->wordArray[i].word);
		llist_print( &wtable->wordArray[i].positions);
	}
}

// Get positions where the word occurs
int save;
LinkedList * wtable_getPositions(WordTable * wtable, char * word)
{
	// Write your code here
	for(int i = 0;i<wtable->nWords;i++){
		if(strcmp(wtable->wordArray[i].word,word) == 0){
		//	save = wtable->wordArray[i].positions->value;
			return &wtable->wordArray[i].positions;
		}
	}
	return NULL;
}

// Conver string to lower case
void toLower(char *s) {
	while(*s){
		if((*s>='A')&&(*s <= 'Z')){
			*s = *s+'a'-'A';
		}
		s++;
	}
}
//
// Separates the string into words
//

#define MAXWORD 200
char word[MAXWORD];
int wordLength;
int wordCount;
int charCount;
int wordPos;

// It returns the next word from stdin.
// If there are no more more words it returns NULL.
// A word is a sequence of alphabetical characters.
static char * nextword(FILE * fd) {
	int c;
	wordPos = 0;
	wordCount = 0;
	int length;
	// While it is not EOF read char
	while((c = fgetc(fd)) != EOF){
		charCount++;
//		printf("%c\n", c);
		//ready to return a word before check whether it is a empty word or not.
		if(!(((c >= 'a')&&(c<='z'))||((c>='A')&&(c<='Z')))){
//			printf("%c\n", c);
			word[wordLength] = '\0';
			length = wordLength;
			wordLength = 0;

			//check if there are more than one space, skip them
			if(word[0] != '\0'){
				wordPos  = charCount - length - 1;
				wordCount ++;
				toLower(word);
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

	return NULL;

}



// Read a file and obtain words and positions of the words and save them in table.
int wtable_createFromFile(WordTable * wtable, char * fileName, int verbose)
{
	// Write your code here
	FILE * fp;
	char * c;
	int i = 0;
	fp = fopen(fileName,"r");
	if(fp == NULL){
		return 0;
	}else{
		while((c = nextword(fp)) != NULL){
			wtable_add(wtable,word, wordPos);
			if(verbose){
				printf("%d: word=%s, pos=%d\n", i, word, wordPos);
				i++;
			}
		}
	}
}

// Sort table in alphabetical order.
void wtable_sort(WordTable * wtable)
{
	WordInfo temp;
	// Write your code here
	for(int i = 0;i<wtable->nWords;i++){
		for(int j = 0;j<wtable->nWords;j++){
			if(strcmp(wtable->wordArray[i].word,wtable->wordArray[j].word)<0){
				temp = wtable->wordArray[i];
				wtable->wordArray[i]= wtable->wordArray[j];
				wtable->wordArray[j] = temp;
			}
		}
	}
}

// Print all segments of text in fileName that contain word.
// at most 200 character. Use fseek to position file pointer.
// Type "man fseek" for more info. 
int wtable_textSegments(WordTable * wtable, char * word, char * fileName)
{
	// Write your code here
	FILE * fp = fopen(fileName,"r");
	char c;
	char save[201];
	int i = 0;
	if(fp == NULL){
		return 0;
	}else{
		if(wtable_getPositions(wtable,word) == NULL){
			return 0;
		}else{
			printf("===== Segments for word \"%s\" in book \"%s\" =====\n",word,fileName);
			LinkedList * list = wtable_getPositions(wtable,word);
			ListNode * e;
			int pos;
			e = list->head;
			while(e != NULL){
				pos = e->value;
				fseek(fp,pos,SEEK_SET);
				for(i;i<200;i++){
					c = fgetc(fp);
					save[i] = c;
				}
				save[i] = '\0';
				printf("---------- pos=%d-----\n",pos);
				printf("......");
				printf("%s",save);
				printf("......\n");
				e = e->next;
				i = 0;
			}
		}
	}
	
}

