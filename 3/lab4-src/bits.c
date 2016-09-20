#include <stdlib.h>
#include <stdio.h>
// It prints the bits in bitmap as 0s and 1s.
void printBits(unsigned int bitmap)
{
	int * bits = (int*)malloc(sizeof(int)*32);
	int a = 0;
	int i = 0;
	int j = 0;
	while(bitmap != 0){
		a = bitmap%2;
		bitmap = bitmap/2;
		*bits = a;
		bits++;
		j++;
	}

	if(j < 32){
		for(j;j<32;j++){
			*bits = 0;
			bits++;
		}
	}

	for(i; i < 32; i++){
		--bits;
		printf("%d",*bits);
	}
	printf("\n");
	printf("10987654321098765432109876543210\n");
}


// Sets the ith bit in *bitmap with the value in bitValue (0 or 1)
void setBitAt( unsigned int *bitmap, int i, int bitValue ) {
	// Add your code here
	if(bitValue == 1){
		int compare = 1 << i;
		*bitmap = compare|*bitmap;
	}
	else if(bitValue == 0){
		int compare = 1 << i;
		*bitmap = (~compare) & (*bitmap);
	}
}

// It returns the bit value (0 or 1) at bit i
int getBitAt( unsigned int bitmap, unsigned int i) {
	// Add your code here
	if(i < 0 || i > 31){
		return -1;
	}else{
		return bitmap>>i&0x01;
	}
}

// It returns the number of bits with a value "bitValue".
// if bitValue is 0, it returns the number of 0s. If bitValue is 1, it returns the number of 1s.
int countBits( unsigned int bitmap, unsigned int bitValue) {
	// Add your code here
	int * bits = (int*)malloc(sizeof(int)*32);
	int a = 0;
	int i = 0;
	int j = 0;
	while(bitmap != 0){
		a = bitmap%2;
		bitmap = bitmap/2;
		*bits = a;
		bits++;
		j++;
	}


	if(j < 32){
		for(j;j<32;j++){
			*bits = 0;
			bits++;
		}
	}


	int count = 0;
	if(bitValue == 0){
		for(i; i < 32; i++){
			--bits;
			if(*bits == 0){
				count++;
			}
		}
		return count;
	}else if(bitValue == 1){
		for(i ; i < 32; i++){
			--bits;
			if(*bits == 1){
				count++;
			}
		}
		return count;
	}

}

// It returns the number of largest consecutive 1s in "bitmap".
// Set "*position" to the beginning bit index of the sequence.
int maxContinuousOnes(unsigned int bitmap, int * position) {
	// Add your code here
	
	int count = 0;
	int save;
	int a;
	int b;
	for(a = 31;a >= 0; a--){
		b = bitmap>>a;
		if(b & 1){
			count ++;
		}else{
			if(save < count){
				save = count;
				*position = a + 1;
				count = 0;
			}else{
				count = 0;
			}
		}
	}
	return save;
}


