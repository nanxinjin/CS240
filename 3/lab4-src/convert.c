#include <stdlib.h>
#include <stdio.h>
#include <string.h>


main(int argc, char ** argv)
{	
	if(argc != 4){
		printf("Usage:  convert <basefrom> <baseto> <number>\n");
		exit(1);
	}
	
	char * baseFromStr = strdup(argv[1]);
	char * baseToStr = strdup(argv[2]);
	char * numberStr = strdup(argv[3]);
	char error;
	char * check = numberStr;


	char * saveChar = (char*)malloc(sizeof(char)*50);
	int * save = (int*)malloc(sizeof(int)*50);
	int baseFrom = atoi(baseFromStr);
	int baseTo = atoi(baseToStr);

	int sum = 0;
	int a = 0;
	int i = 0;
	int count = 0;
	int zero = 0;


// Convert all baseFrom to base 10, save it as "sum"
	if(baseFrom != 10){
		int t = 0;
		for(i ; numberStr[i];i++){
			if(numberStr[i]<='9'){
				t = numberStr[i] - '0';
			}else{
				t = numberStr[i]-'A'+10;
			}
			sum = sum * baseFrom + t;
		}
	}else{
		sum = atoi(numberStr);
	}
	//printf("%d",sum);
	printf("Number read in base %d: %s\n",baseFrom,numberStr);

// Check wrong digit of input
	if(!strcmp(baseFromStr,"5")){
		error = '5';
		while(*check){
			if(error<*check){
				printf("Wrong digit in number.\n");
				exit(1);
			}
			check++;
		}
	}else if(!strcmp(baseFromStr,"8")){
		error = '8';
		while(*check){
			if(error<*check){
				printf("Wrong digit in number.\n");
				exit(1);
			}
		check++;
		}
	}else if(!strcmp(baseFromStr,"16")){
		error = 'G';
	        while(*check){                                  
			if(error<*check){                                                               
				printf("Wrong digit in number.\n");                                                                             
				exit(1);                                                                                                                
			}                                                                                                                                               
			check++;
		}
	}else if(!strcmp(baseFromStr,"25")){
		error = 'P';
	        while(*check){                                                                                  
			if(error<*check){                                                                                                                               
				printf("Wrong digit in number.\n");                                                                                                                                
				exit(1);                                                                                                                                                           
			}        
			check++;                                                                                                                                                        
		}
	}

	printf("Converted to base 10: %d\n",sum);
	if(baseTo == 10){
		printf("Converted to base %d: %d\n",baseTo,sum);
		exit(1);
	}else if(baseTo == 2){
		count = 0;
		zero = 0;
		while(sum != 0){
			
			a = sum%2;
			sum/=2;
			*save = a;
			save ++;
			count ++;
		
		}
		printf("Converted to base %d: ",baseTo);
		for(zero;zero<count;zero++){
			--save;
			printf("%d",*save);
		}
		printf("\n");
		
	}else if(baseTo == 8){
		count = 0;
		zero = 0;
		while(sum != 0){
			a = sum%8;
			sum/=8;
			*save = a;
			save ++;
			count ++;
		}
			printf("Converted to base %d: ",baseTo);
			for(zero;zero<count;zero++){
				--save;
				printf("%d",*save);
			}
			printf("\n");
	}else {
		count = 0;
		zero = 0;
		char c;
		while(sum != 0){
			a = sum%baseTo;
			if(a > 9){
				c = a-10+'A';
				
			}else if(0<=a<=9){
			// convert int number to char number
				c = a + '0';
			}
			sum/=baseTo;
			*saveChar = c;
			saveChar ++;
			count ++;
	
		}
		printf("Converted to base %d: ",baseTo);
		for(zero;zero<count;zero++){
			--saveChar;
			printf("%c",*saveChar);
		}
		printf("\n");
	}
}
