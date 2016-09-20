
#include <stdio.h>
#include <stdlib.h>
#include "resizable_table.h"

void
printUsage() {
	printf("Usage: wordcount [-w|-s] file\n");
}

int
main(int argc, char **argv) {
	if ( argc < 2) {
		printUsage();
		exit(1);
	}
	if(!strcmp(argv[1],"-w")) {
	RESIZABLE_TABLE *rt;
	rt = rtable_create();
	FILE *fp;
	char a;
	fp = fopen(argv[2], "r");
	do{
		int i = 0;
		char * name = malloc(20);
		do{
			a = fgetc(fp);
			if(a>64){
				if(a>96) {
					name[i] = a;
				}
				else {
					name[i] = a+32;
				}
				i++;
			
			}
		}while(a>64 && a != EOF);
		if(name[0] != NULL) {
			printf("%s\n",name);
		}
	}while(a != EOF);
	rtable_print_int(rt);
	fclose(fp);
	}
	// Add your implementation here

	exit(0);
}


