
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char ** argv) {
	int c;
	int lines=0;
	if(argc < 2){
		printf("Usage: countlines filename\n");
		exit(1);
	}
 	// Add your implementation here
	char *fileName = argv[1];
	FILE *fd = fopen(fileName,"r");
	if(fd == NULL){
		printf("Could not open file %s\n,fileName");
		exit(1);
	}
	
	while((c=fgetc(fd))!= EOF){
		if(c == '\n'){
			lines ++;
		}
	}
	printf("Program that counts lines.\n");
	printf("Total lines: %d\n",lines);
	exit(0);
}
