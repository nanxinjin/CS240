#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int jnx(int dishu, int a){
        int value = dishu;
	 int i = 1;
	 if(a == 0){
	 	return 1;
	}
	else{
		for(i = 1; i < a;i++){
			value = value * dishu;
		}
		return value;
		}
																}

int convertToTen(char * numbers, int dishu){
	int left;
	int a = 0;
	int resultValue = 0;
	int cd = strlen(numbers);

	do{
		if(numbers[cd - a - 1] <= '9'  && numbers[cd - a - 1] >= '0' ){
			left = numbers[cd - a - 1] - '0';
		}
		else {
			left = numbers[cd - a - 1] - 'A'+ 10;
		}
		if(left > dishu){
			return -1;
		}else{
			resultValue = resultValue + left * jnx(dishu, a);
			a++;
		}

	}while(a != cd);

	return resultValue;
}

char * dyx(char * w){
	char * m = (char*)malloc(sizeof(char) * strlen(w));
	int cd = strlen(w);
	int a = 0;

	for(a; a< cd; a++){
		*(m + a) = *(w + cd - a - 1);
	}
	return m;
}


main(int argc, char **argv)
{
	if(argc < 4){
		printf("Usage:  convert <basefrom> <baseto> <number>\n");
	}
	else{
		int fromWhat = atoi(argv[1]);
		int toWhat = atoi(argv[2]);
		int b10;
		printf("Number read in base %d: %s\n", fromWhat, argv[3]);
		b10 = convertToTen(argv[3],fromWhat);
		if(b10 == -1){
			printf("Wrong digit in number.\n");
		}
		else{
			printf("Converted to base 10: %d\n",b10);
			char * j = (char* )malloc(32 * sizeof(char));
			int a =0;
			do{
				int left = b10 % toWhat;
				if(left <= 9) {
					j[a] = left + '0';
				}
				else{
					j[a] = left + 'A' - 10;
				}
				b10 = b10 / toWhat;
				a++;
			}while(b10 != 0);
			char * j2 = (char*)malloc(32 * sizeof(char));
			j2 = dyx(j);
			printf("Converted to base %d: %s\n",toWhat, j2);
		}
	}
}
