#include <stdio.h>

 main() {
  int flag;
  printf("Welcome to the High Low game...\n");


  while(1){  
    printf("Think of a number between 1 and 100 and press press <enter>");
    int a;
    a = getchar(); 
    if(a == '\n') {
      int max = 100;
      int min = 1;
      int mid;

    while(1) {
	mid = (max+min)/2;
	printf("Is it higher than %d? (y/n)\n", mid);
    	flag = getchar();
      getchar();

      if (flag == 'y') {
        min = mid + 1;
      } 
      else if (flag == 'n') {
        max = mid - 1;
      }
      else {
        printf("Type y or n\n");
        continue; 
      }
      if (min>max) {
	mid=min;
        break;
      }
    }
   
 printf("\n");
   printf(">>>>>> The number is %d\n\n", mid);
    
  printf("Do you want to continue playing (y/n)?");
  flag = getchar();
  getchar();
  
  if(flag == 'y') {
    continue;
  }
  else if (flag == 'n') {
    printf("Thanks for playing!!!\n");
    printf("cs240@data ~/cs240/lab1-src-sol $");
    break;
  }
	
  }
}}
