#include <stdio.h>

int
main(int argc, char **argv) {
	printf("Welcome to the High Low game...\n");
//	printf("Think of a number between 1 and 100 and press press <enter>\n");
//	getchar();
  // Write your implementation here...
  	int low = 1;
	int high = 100;
	int mid = 50;
	while(1){
		printf("Think of a number between 1 and 100 and press press <enter>\n");
		getchar();
		while(high >= low){
			mid = (low + high)/2;
			printf("Is it higher than %d? (y/n)\n",mid);
			int answer;
			answer = getchar();
			getchar();
			if(answer == 'y'){
				low = mid + 1;
			}
			else if(answer == 'n'){
				high = mid - 1;	
			}else{
				printf("Type y or n\n");
			}	
		}
		printf("\n");
		printf(">>>>>> The number is %d\n\n",low);
		printf("Do you want to continue playing (y/n)?\n");
		int again;
		again = getchar();
		getchar();
		if(again == 'n'){
			break;	
		}
		else if(again == 'y'){
			low = 1;
			 high = 100;
			 mid = 50;
		}
	}
	printf("Thanks for playing!!!\n");
}


