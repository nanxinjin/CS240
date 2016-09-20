#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//
// Sort an array of element of any type
// it uses "compFunc" to sort the elements.
// The elements are sorted such as:
//
// if ascending != 0
//   compFunc( array[ i ], array[ i+1 ] ) <= 0
// else
//   compFunc( array[ i ], array[ i+1 ] ) >= 0
//
// See test_sort to see how to use mysort.
//
void mysort( int n,                      // Number of elements
	     int elementSize,            // Size of each element
	     void * array,               // Pointer to an array
	     int ascending,              // 0 -> descending; 1 -> ascending
	     CompareFunction compFunc )  // Comparison function.
{
	char * store = (char *)malloc(elementSize);
	int rem,x,y,z;
	for(x = 0;x<n;x++){
		z = x;
		for(y=x+1;y<n;y++){
			rem = compFunc((char *)array+elementSize*z,(char *)array+elementSize*y);
			if(ascending==0&&rem<=0||ascending==1&&rem>=0){
				z = y;
			}
		}
		memcpy(store,(char *)array+elementSize*x,elementSize);
		memcpy((char *)array+elementSize*x,(char *)array+elementSize*z,elementSize);
		memcpy((char*)array+elementSize*z,store,elementSize);
	}
	free(store);
}

