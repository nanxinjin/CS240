#include "stdlib.h"
#include "stdio.h"
#include "Sound.h"
#include "string.h"

int main(int argc, char ** argv){
	if(argc < 2){
		printf("error(lose parameter)\n");
		exit(5);
	}

	Sound * s1 = new Sound(1,44000,2);
	Sound * s2 = new Sound(1,44000,2);
	Sound * s3 = new Sound(1,44000,2);
	
	s2->read("words/pause.wav");
	
	char * p1 = (char*)malloc(strlen(argv[1]+1));
	strcpy(p1,argv[1]);
	



	char * x;
	x = strtok(p1, " ");


	char * y = (char*)malloc(strlen(x) + 11);
	strcpy(y,x);
	strcat(y,".wav");
	

	if(s1->read(y)){
	}else{
		printf("error(not exist)\n");
	}
	
	free(y);

	while((x = strtok(NULL, " "))!= NULL){
		 y = (char*)malloc(strlen(x) + 11);
		strcpy(y,x);
		strcat(y,".wav");

		if(s3->read(y)){
		}else{
			printf("error(not exist)\n");
		}
		free(y);
		s1->append(s2);
		s1->append(s3);
	}
	
	char * save = argv[2];
	s1->write(save);
}

