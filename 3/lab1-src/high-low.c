#include <stdio.h>
//

int
main(int argc, char **argv) {
	printf("Welcome to the High Low game...\n");
	
  // Write your implementation here...
	int low = 1;
	int high = 100;
	int mid;
	char c;
	while(1){
		printf("Think of a number between 1 and 100 and press <enter>\n");
		getchar();

		
		while(1){
			mid = (low + high)/2;
			if (high < low){
				printf("\n");
				printf(">>>>>> The number is %d\n\n",low);
				break;
			}
			printf("Is it higher than %d? (y/n)\n",mid);
			scanf("%c",&c);
			getchar();
			if(c == 'y'){
				low = mid + 1;
			}else if(c == 'n'){
				high = mid - 1;
			}else{
				printf("Type y or n\n");
			}
		}
//play again 
		printf("Do you want to continue playing (y/n)?");
		char answer;
		scanf("%c",&answer);
		getchar();
		if (answer == 'n'){
			break;
		}else if (answer == 'y'){
			low = 1;
			high = 100;
			char c = NULL;
			mid = 0;
		}
	}
		
	printf("Thanks for playing!!!\n");
	
}

