
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mymemdump(FILE * fd, char * p , int len) {
    // Add your code here.
    // You may see p as an array.
    // p[0] will return the element 0 
    // p[1] will return the element 1 and so on
  int sign = 0;
  int sign2 = 0;
  int j = 0;
  int k = 0;
  int c;
  for(int i = 0; i < len; i+=16){
    fprintf(fd, "0x%016lX: ", (unsigned long) &p[i]);
    for(j = sign;j < 16 + sign; j++){
    		if(j>=len){
			for(j;j<16+sign;j++)
				fprintf(fd,"   ");
			break;
		}
    		int c = p[j]&0xFF;
		fprintf(fd, "%02X",c);
		fprintf(fd, " ");
  	}
	//printf("%d\n",j);
	sign = j;
  	fprintf(fd," ");
    // Print first byte as hexadecimal
    for(k = sign2;k < 16 +sign2; k++){
		int c = p[k]&0xFF;
		if(k < len){
			fprintf(fd,"%c",(32<=c && c<=127)?c:'.');
		}else{}
     }
	sign2 = k;
    // Print first byte as character
    fprintf(fd,"\n");
	}
}


