
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mymemdump(FILE * fd, char * p , int len) {
    // Add your code here.
    // You may see p as an array.
    // p[0] will return the element 0 
    // p[1] will return the element 1 and so on
    int c;
    int test;
    int flag = 0;
    int flag2 = 0;
    int j = 0;
    int k = 0;

  for (int i = 0; i < len ; i+=16) {
    fprintf(fd, "0x%016lX: ",(unsigned long) &p[i]);  
    // Print first byte as hexadecimal
    for (j = flag; j < 16 + flag; j++) {    
      int c = p[j]&0xFF;
      if (j < len) {
        fprintf(fd, "%02X ", c);
      }else{
        fprintf(fd, "   ");
      }
    }
    flag = j;
    // Print first byte as character
    fprintf(fd, " ");
    for (k = flag2; k < 16 + flag2; k++) {
      int c = p[k]&0xFF;
      if (k < len) {
        fprintf(fd, "%c", (c>=32)?c:'.');
      } else {
        
      }
    }
    flag2 = k;
    fprintf(fd,"\n");  
    
  }
    
}

