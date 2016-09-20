#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Problem ( 1/3 ) 
/******************************************************************************
 * TODO: Count the number of lines in the file named 'fileName'. Return the 
 * number of lines as an integer.
 * 
 * Parameters: fileName -- name of the file
 *
 * Return: number of lines in the file
 *
 * Return Type: integer
 *****************************************************************************/
int countLines(char * fileName) {
    // Write Your Code Here
    FILE *fd;
    fd = fopen(fileName, "r");
    if(fd == NULL){
    	printf("Could not open file %s\n",fileName);
	exit(1);
    }
    int c;
    int line = 0;
    while((c = fgetc(fd)) != EOF){
    	if(c == '\n'){
		line++;
	}
    }
    return line;
}

// Problem ( 2/3 ) 
/******************************************************************************
 * TODO: Read the text file, parse each word, and store the word in to the
 * 'word_list'. Change all the characters in the word to capital letters. 
 * Return 'word_list'.
 *
 * E.g. a text file contains "Hello, world"
 *      The string array 'word_list' should contain {"HELLO", "WORLD"}
 * 
 * Parameters: fileName -- name of the file
 *             word_list -- seperate the words from the text file and store
 *             each word in to this string array. Make sure to change all the
 *             characters in the word to upper case.
 *
 * Return: return the string array 'word_list'
 *
 * Return Type: char double pointer (String array)
 *****************************************************************************/
char ** create_word_list( char * fileName, char ** word_list ) {
    // Write Your Code Here
    FILE * fd;
    fd = fopen(fileName,"r");
    if(fd == NULL){
    	printf("Could not open file %s\n",fileName);
	exit(1);
    }
    int i = 0;
    int k = 0; //dash-indicator
    int j;
    char *p;
    char * word = (char*)malloc(sizeof(char)*50);
    while(fscanf(fd, "%s", word)!= EOF)
      {
	p = word;
	while (*p != '\0') {
	  if(*p == '.' || *p == ',' || *p == ':' || *p == ' ' || *p == '?' || *p == ';' || *p == '\n') {//check if word contain . or , sign
	   *p = '\0';
	    break;
	  }
	  *p = toupper(*p);//setall char to upper case
	  p++;
	}
	p = word;
	while(*p != '\0') { //This loop check dash
	  if (*p == '-') {
	    *p = '\0';
	    k = 1;
	    break;
	  }
	  p++;
	}
	p = word;
	while(*p != '\0'){
		if(*p == '?'){
			*p = '\0';
			k = 1;
			break;
		}
		p++;
	}
	word_list[i] = strdup(word);//add word into list
	i++;
	if (k == 1) { //if contains dash, add word after dash into list
	  p++;
	  word_list[i] = strdup(p);
	  i++;
	  k=0;
	}
	word[0] = '\0';
	}
    return word_list;

}

// Problem ( 3/3 ) 
/******************************************************************************
 * TODO: Iterate through the list of words in each file. If a word is found in
 * both files, add the word to 'match_list'. Do not repeat words in the list. 
 * Capitilization of words does not matter. So "Bob" and "bob" should be
 * considered a match. When inserting the word in to the list, make all the
 * characters in the word upper case. 
 *
 *  HINT: Use the function create_word_list to save time.
 *
 * E.g. File1 contains the text "We like fruit. It is good."
 *      File2 contains the text "Fruit is very delicious."
 *
 *      The string array 'match_list' should contain {"FRUIT", "IS"}
 *
 * Parameters: fileName1 -- name of the first text file
 *	       fileName2 -- name of the second text file
 *	       match_list -- store the intersecting words from both files in
 *	                     this string array. 
 *
 * Return: Return the string array 'match_list'.
 *
 * Return Type: char double pointer (String array)
 *****************************************************************************/
char ** sharedWords( char * fileName1, char * fileName2, char ** match_list ) {
    // Write Your Code Here
    //printf("111111111111111111111111111111111111111111111111\n");
    char ** file1 = (char**)malloc(sizeof(char*)*200);
    char ** file2 = (char**)malloc(sizeof(char*)*200);
    //match_list = (char**)malloc(sizeof(char*)*200);
    char ** fileStore = (char**)malloc(sizeof(char*)*200);
    create_word_list(fileName1,file1);
    create_word_list(fileName2,file2);
    //test
    int i = 0;
    int j = 0;
    int k = 0;

//find the same word
    while(file1[i] != NULL){
    	while(file2[j] != NULL){
		if(strcmp(file1[i],file2[j]) == 0){
			fileStore[k] = strdup(file2[j]);
			k++;
		}
		j++;
	}
	i++;
	j = 0;
    }
//make sure every word appear just one time in match_list
	k = 0;
	i = 0;
	j = 0;
	int flag = 1;
	//Iterate fileStore
	while(fileStore[k] != NULL){
	//compare all of word in Match_list every time
		while(match_list[i] != NULL){
	//if find same word in match_list, then quit while loop and compare next word in fileStore
			if(strcmp(fileStore[k], match_list[i]) == 0){
				k++;
				i = 0;
				flag = 0;
				break;
	//if all of word are different
			}else{
				flag = 1;
				i++;
			}
		}
	//if all of word are different between match_list and fileStore, then store that word in match_list
		if(flag){
			match_list[j] = strdup(fileStore[k]);
			j ++;
			i = 0;
			k++;
		}
	}
// test output
	//	i = 0;
 	//   for(i;i<200;i++){
  	//  	printf("fileStore:%s\n",fileStore[i]);
   	//	printf("file2:%s\n",file2[i]);
   	// }
    	//
    return match_list;
}
