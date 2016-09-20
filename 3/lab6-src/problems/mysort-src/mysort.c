#include "mysort.h"
#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

//

//
// See test_sort to see how to use mysort.
/**
 * @brief Arbitrary sort func
 *
 * Sort an array of element of any type
 * using "compFunc" to sort the elements.
 * 
 * The elements are sorted such as:
 * 
 * if ascending != 0
 *   compFunc( array[ i ], array[ i+1 ] ) <= 0
 * else
 *   compFunc( array[ i ], array[ i+1 ] ) >= 0
 * 
 * @param n Number of elements.
 * @param elementSize Size of each element.
 * @param array Pointer to an array of arbitrary type.
 * @param ascending Boolean controlling the direction of the sort.
 * @param compFunc Comparison funciton.
 **/
void mysort(int n, int elementSize, void * array, int ascending, CompareFunction compFunc)
{
	/** @todo **/
	void * temp = malloc(elementSize);
	int i = 0;
	int j = 0;
	for(i;i<n-1;i++){
		for(j;j < n-1;j++){
			void * e1 = (void*)((char*)array + j*elementSize);
			void * e2 = (void*)((char*)array + (j+1)*elementSize);
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

