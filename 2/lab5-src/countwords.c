
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct WordInfo {
	char * word;
	int count;
};

typedef struct WordInfo WordInfo;

int maxWords;
int nWords;
WordInfo*  wordArray;

#define MAXWORD 100
int wordLength;
char * word;
FILE * fd;
int charCount;
int wordPos;

void toLower(char *s) {
  int i = 0;
  while(s[i] != '\0')
    {
      s[i] = tolower(s[i]);
      i++;
    }
  return;
}

void sort() {
  int i, j;
  WordInfo temp;
  for (i = 0; i < nWords - 1; i++)
    {
      for (j = 0; j < nWords - i - 1; j++)
	{
	  if (strcmp(wordArray[j].word,wordArray[j+1].word) > 0)
	    {
	      temp = wordArray[j];
	      wordArray[j] = wordArray[j+1];
	      wordArray[j+1] = temp;
	    }
	}
    }
}

// It returns the next word from stdin.
// If there are no more more words it returns NULL. 
static char * nextword() {
  char w[MAXWORD];
  int i = 0;
  int ch;

  while((ch=fgetc(fd)) != EOF && !isalpha(ch))
    ;
  if (ch == EOF)
    return NULL;
  do{
    w[i++] = ch;
  }while((ch=fgetc(fd)) != EOF && isalpha(ch));

  w[i] = '\0';
  return strdup(w);
}

int
main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Usage: countwords filename\n");
		exit(1);
	}

	char * filename = argv[1];

	fd = fopen(filename, "r");
	if (fd == NULL)
	  {
	    printf("File not found\n");
	    exit(1);
	  }

	maxWords = 100;
	nWords = 0;
	wordArray = (WordInfo*)malloc(sizeof(WordInfo) * maxWords * 2);

	int i;
	int k = 0;
	while((word = nextword()) != NULL)
	  {
	    toLower(word);
	    if (word != NULL && strlen(word) != 0) {
	      for (i = 0; i < nWords; i++)
		{
		  if(strcmp(wordArray[i].word,word) == 0) {
		    wordArray[i].count++;
		    k = 1;
		    break;
		  }
		}
	      if (k == 0) {
		wordArray[i].word = strdup(word);
		wordArray[i].count = 1;
		nWords++;
	      }
	      k = 0;
	    }
	  }
	sort();
	for (i = 0; i < nWords; i++)
	  {
	    printf("%s %d\n", wordArray[i].word,wordArray[i].count);
	  }
	    
}

