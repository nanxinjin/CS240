
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char ** argv) {
	int c;
	int lc;
	int lines=0;
	
 	// Add your implementation here
	printf("Program that counts lines.\n");
	if(argc < 2){
		printf("Usage: countlines filename\n");
		exit(1);
	}

	//get files
	char * fileName = argv[1];
	FILE * fd = fopen(fileName, "r");
	if(fd == NULL){
		printf("Could not open file %s\n", fileName);
		exit(1);
	}

	while((c = fgetc(fd)) != -1){
		//test 
		//printf("TEST c = %c\n", c);
		
		//
		if(c == '\n'){
			lines ++;
		}
		lc = c;
	}
	
	fclose(fd);
	if(lc != '\n'){
		lines++;
	}
	printf("Total lines: %d\n", lines);

}
