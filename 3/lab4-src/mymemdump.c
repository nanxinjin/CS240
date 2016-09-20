
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mymemdump(FILE * fd, char * p , int len) {
    // Add your code here.
    // You may see p as an array.
    // p[0] will return the element 0 
    // p[1] will return the element 1 and so on
    
    int i;
    int sign = 0;
    int sign2 = 0;
    int c;
    int j = 0;
    int k = 0;
   // fprintf(fd, "0x%016lX: ", (unsigned long) p); // Print address of the beginning of p. You need to print it every 16 bytes


    for (i=0; i < len; i+=16) {
	fprintf(fd, "0x%016lX: ", (unsigned long) &p[i]);
	for(j = sign;j<16 + sign;j++){
		if(j >= len){
			for(j;j<16+sign;j++){
				fprintf(fd,"   ");
			}
			break;
		}
		c = p[j]&0xFF;
		fprintf(fd, "%02X",c);
		fprintf(fd," ");
	}

        // Get value at [p]. The &0xFF is to make sure you truncate to 8bits or one byte.
	sign = j;
	fprintf(fd, " ");
        // Print first byte as hexadecimal
	for(k = sign2;k<16+sign2;k++){
		c = p[k]&0xFF;
		if(k<len){
			fprintf(fd,"%c",(32<=c && c<=127)?c:'.');
		}else{}
	}
	sign2 = k;
        // Print first byte as character. Only print characters >= 32 that are the printable characters.

        fprintf(fd,"\n");
      
    }

}

