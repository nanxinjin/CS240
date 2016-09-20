#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
	if(argc < 1){
		printf("Input k?\n");
	}else{
		printf("Program Fibonacci\n");
		int flag = 1;
		while(flag){
			printf("Input k?");
			int fa = 0;
			int fb = 1;
			int fc = fa+fb;
		
			char* inPut = argv[1];
			int kth;
			kth = atoi(inPut);
			if(kth = 1){
				fc = 1;
			}else if(kth > 1){
				int i  = 0;
				for(i;i<kth;i++){
					fc = fa + fb;
					fa = fb;
					fb = fc;
				}
			}
			printf("The %dth Fibonacci number is %d",kth,fc);
			printf("Do you want to continue y/n?\n");
			char a;
			scanf("%c,&a");
			if(a == 'y'){
				flag = 1;
			}else if(a == 'n'){
				break;
			}
		}
		printf("Bye!\n");

	}
}
