#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char ** argv) {
	char c;
	int account;
	char * words;
	words = (char*)malloc(10000);
	int i = 0;
	int j = 0;
	int space = 0;
	int delete = 0;
	printf("Program to separate text to words. Type a string and ctrl-d to exit\n");
	while ((c=getchar()) != -1){
		words[i] = c;
		i++;
	}

		printf("Word %d: ",space);
		space++;


/*
		// delete space
		while(words[space] != '\0'){
			if(words[space] != ' ' || words[space + 1] != ' '){
				words[delete] = words[space];
				delete ++;
				space ++;
			}
			else{
				words[delete] = words[space + 1];
				space ++;
			}
		}
		words[delete] = '\0';
*/



		for(j;words[j] != '\0';j++){
			if (words[j] == ' ' || words[j] == '\n'){

				if(words[j-1] != ' ' && words[j-1] != '\n' && j != strlen(words)-2 && j!= strlen(words)-1) {
					printf("\n");
					printf("Word %d: ",space);
					space++;
				}/*
				else if(words[j-1] != ' ' && words[j-1] != '\n' && j != strlen(words)-1  ){
					printf("\n");
					printf("Word %d: ",space);
					space++;
				}
			
			*/
				delete = j;
		//		printf("j:%d,words[j]:%c",j,words[j]);
				for(delete; words[delete] == ' ' || words[delete] == '\n' ;delete++){
					j=delete;
				//	printf("%d",delete);
				}
				j = delete - 1;
			}
			
			else if ('a'<=words[j]<='z'){
				printf("%c",words[j]);
			}
			
		}
	
					printf("\n");
	printf("words total = %d\n",space);
	
	
}

