
#include <stdio.h>

#include "array.h"

// Return sum of the array
double sumArray(int n, double * array) {
  double sum = 0;
  
  double * p = array;
  double * pend = p+n;

  while (p < pend) {
    sum += *p;
    p++;
  }

  return sum;
}

// Return maximum element of array
double maxArray(int n, double * array) {
	double max = 0;

	double * p = array;
	double * pend = p + n;

	while (p < pend){
		if(*p>max){
			max = *p;
		}
		p++;
	}
	return max;
}

// Return minimum element of array
double minArray(int n, double * array) {
	double min = 0;

	double * p = array;
	double * pend = p + n;

	while(p < pend){
		if(*p < min){
			min = *p;
		}
		p++;
	}
	return min;
}

// Find the position int he array of the first element x 
// such that min<=x<=max or -1 if no element was found
int findArray(int n, double * array, double min, double max) {
  	double * p = array;
	double * pend = p + n;
	int position = 0;
	
	while(p < pend){
		if(*p>=min && *p<=max){
			return position;
		}else{
			position ++;
			p++;
		}
	} 
	return -1;
}

// Sort array without using [] operator. Use pointers 
// Hint: Use a pointer to the current and another to the next element
int sortArray(int n, double * array) {
	double * p = array;
	double * pend = p + n;
	double * compare = p + 1;
	double store = 0;
	while(p < pend){
		while(compare < pend){
			if(*p>*compare){
				store = *compare;
				*compare = *p;
				*p = store;
			}
			compare ++;
		}
		p++;
		compare = p+1;
	} 
}

// Print array
void printArray(int n, double * array) {
	double * p = array;
	double * pend = p + n;
	int line = 0;
	while(p < pend){
		printf("%d:%lf\n",line,*p);
		p++;
		line++;
	}
}

