//#include <iostream>
//#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "WordIterator.h"

WordIterator::WordIterator()
{
}

bool
WordIterator::readFile(const char * fileName)
{
	
	if((_fd = fopen(fileName, "r")) == NULL){
		printf("error on open file\n");
//		getch();
		return false;
		exit(1);
	}
	

	return true;
}

const char * 
WordIterator::next()
{
	int c;
	int i = 0;
	char * str;
	str = (char*)malloc(sizeof(char)*20);
 
	while((c = fgetc(_fd)) != '\0' ){

		if(c == ' ' || c == '\n'){
			str[i ] = '\0';
				if(str[0] != '\0'){
					return str;
					
				}else{
					
				}
		}else if(c == EOF){
			return NULL;
		}
		else{
			str[i] = c;
			i++;
		}
	}
}

WordIterator::~WordIterator()
{

}

