
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 80

// Generate Cellular Automaton strings based on 
// http://mathworld.wolfram.com/ElementaryCellularAutomaton.html

main(int argc, char ** argv)
{	// get rule number from argument
	if (argc < 2) {
		printf("Usage: life rule-number\n");
		exit(1);
	}
	
	int input = (atoi)(argv[1]);
	printf("Rule number:%d\n",input);
	if(input >= 256){
		printf("Rule out of bounds. 0 <= rule-number < 256\n");
		exit(1);
	}
		


	// Convert rule number to array
	int c,k;
	int i = 0;
	char rule[8];
//	char * rule = (char)malloc(8*sizeof(char));
	for (c = 7; c>=0;c--){
		k = input >>c;
		if(k & 1){
			rule[7-i] = '1';
			i++;
		}else{
			rule[7-i] = '0';
			i++;
		}
	}		
	
	rule[8] = '\0';

	//print rules
	printf("Rules:\n");
	printf("000=>%c\n",rule[0]);
        printf("001=>%c\n",rule[1]);
	printf("010=>%c\n",rule[2]);
	printf("011=>%c\n",rule[3]);
	printf("100=>%c\n",rule[4]);
	printf("101=>%c\n",rule[5]);
	printf("110=>%c\n",rule[6]);
	printf("111=>%c\n",rule[7]);


//	printf("%s\n",rule);

	// Initialize initial string. A string of 80 spaces with a * in the middle.
	char * str1 = (char*)malloc(80*sizeof(char));
	int first = 0;
	for (first; first < 80;first ++ ){
		str1[first] = ' ';
	}
	str1[40] = '*';
	printf("%s\n",str1);

	int times = 0;
	// Generate 40 subsequent strings based on rules
	for(times; times<40;times++){

	char * str2 = (char*)malloc(80*sizeof(char));
	char str3[3];
	str2[0] = ' ';
	int loop = 0;
	str3[3] = '\0';
		for(loop; loop <=78;loop++){
			str3[0] = str1[loop];
			str3[1] = str1[loop + 1];
			str3[2] = str1[loop + 2];
			if(strcmp(str3,"   ") == 0){
				str2[loop + 1] = rule[0];
			}
			else if(strcmp(str3,"  *") == 0){
				str2[loop + 1] = rule[1];
			}
			else if(strcmp(str3," * ") == 0){
				str2[loop + 1] = rule[2];
			}
			else if(strcmp(str3," **") == 0){
				str2[loop + 1] = rule[3];
			}
			else if(strcmp(str3,"*  ") == 0){
				str2[loop + 1] = rule[4];
			}
			else if(strcmp(str3,"* *") == 0){
				str2[loop + 1] = rule[5];
			}
			else if(strcmp(str3,"** ") == 0){
				str2[loop + 1] = rule[6];
			}
			else if(strcmp(str3,"***") == 0){
				str2[loop + 1] = rule[7];
			}
			if(str2[loop+1] == '1') {
				str2[loop+1] = '*';
			}
			else {
				str2[loop+1] = ' ';
			}
		}
//		printf("%s\n",rule);
		printf("%s\n",str2);

		str2[79] = ' ';	
		str1 = str2;
	}
}







