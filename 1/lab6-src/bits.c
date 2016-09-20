#include<stdio.h>

// It prints the bits in bitmap as 0s and 1s.
void printBits(unsigned int bitmap)
{
	// Add your code here
	int c, k;
	for (c = 31; c >= 0; c--){
		k = bitmap >> c;
		if(k & 1){
			printf("1");
		}else{
			printf("0");
		}
	}
	printf("\n");
	printf("10987654321098765432109876543210\n");
	
}


// Sets the ith bit in *bitmap with the value in bitValue (0 or 1)
void setBitAt( unsigned int *bitmap, int i, int bitValue ) {
	if(bitValue == 1){
		int compare = 1 << i;
		*bitmap = compare|*bitmap;
	
	}
	else if(bitValue == 0){
		int compare = 1 << i;
		*bitmap = (~compare) & (*bitmap);
		
	}
	// Add your code here
}

// It returns the bit value (0 or 1) at bit i
int getBitAt( unsigned int bitmap, unsigned int i) {
	int k;
	k = bitmap >> i;
	if(k & 1){
		return 1;
	}else{
		return 0;
	}
	
	// Add your code here
}

// It returns the number of bits with a value "bitValue".
// if bitValue is 0, it returns the number of 0s. If bitValue is 1, it returns the number of 1s.
int countBits( unsigned int bitmap, unsigned int bitValue) {
	// Add your code here
	int count = 0;
	if(bitValue == 1){
		int c,k;
		for(c = 31; c>=0;c--){
			k = bitmap>>c;
			if(k & 1){
				count ++;
			}
		}
		return count;
	}else if(bitValue == 0){
		int c,k;
		for(c = 31; c>=0;c--){
			k = bitmap>>c;
			if(k & 1 ){
				count++;
			}
		}
		count = 32 - count;
		return count;
	}

}

// It returns the number of largest consecutive 1s in "bitmap".
// Set "*position" to the beginning bit index of the sequence.
int maxContinuousOnes(unsigned int bitmap, int * position) {
	// Add your code here
	int count = 0;
	int save;
	int c,k;
	for(c = 31; c>=0;c--){
		k = bitmap>>c;
		if(k & 1){
			count ++;
		}else{
			if(save < count){
				save = count;
				*position = c + 1;
				count = 0;
			}else{
				count = 0;
			}
		}
	}
	return save;
}


