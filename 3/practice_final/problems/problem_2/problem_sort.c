#include "sort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

// Problem (1/1)
/******************************************************************************
 * TODO: Sort an array of elements of any type. Use the 'compFunc' to sort the
 * elements. 
 *
 * Parameters: n -- number of elements in the array
 *             elementSize -- the size of each element
 *             array -- pointer to an array of arbitrary size
 *             ascending -- 
 *             compFunc -- the comparison function
 *
 * Return: void
 *
 * Return Type: void
 *****************************************************************************/
void mysort(int n, int elementSize, void * array, int ascending, CompareFunction compFunc)
{
	// Write Your Code Here
	void * temp = malloc(elementSize);
	int i = 0;
	int j = 0;
	for(i; i < n - 1;i++){
		
		for(j;j<n-1;j++){
			void * e1 = (void*)((char*)array + j*elementSize);
			void * e2 = (void*)((char*)array+(j+1)*elementSize);
			if(ascending == 1){
				if((*compFunc)(e1,e2)>0){
					memcpy(temp,e1,elementSize);
					memcpy(e1,e2,elementSize);
					memcpy(e2,temp,elementSize);
				}
			}else if(ascending == 0){
				if((*compFunc)(e1,e2)<0){
					memcpy(temp,e1,elementSize);
					memcpy(e1,e2,elementSize);
					memcpy(e2,temp,elementSize);
				}
			}
		}
		j = 0;
	}
	free(temp);
}

