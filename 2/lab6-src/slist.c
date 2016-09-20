
#include <stdio.h>
#include <stdlib.h>

#include "slist.h"

void
sllist_init(SLList * list)
{
	list->head = NULL;
}

// Add int value to the end of list. The values may be repeated.
void
sllist_add_end( SLList *list, int value )  {
	SLEntry *e;
	SLEntry *insert;
	e = list->head;
	insert = NULL;
	if(e == NULL){
		e = (SLEntry *)malloc(sizeof(SLEntry));
		e->value = value;
		list->head = e;
	}else{
		while(e != NULL){
			insert = e;
			e = e->next;
		}
		e = (SLEntry *)malloc(sizeof(SLEntry));
		e->value = value;
		insert->next = e;
	}	
}


// Remove first occurrence of value in the list. It returns 1 if value is found or 0 otherwise.
int sllist_remove(SLList *list, int value) {
	SLEntry * prev;
	SLEntry * e;
	e = list->head;
	prev = NULL;
	while(e != NULL){
		if(e->value == value && e==list->head){
			prev = e->next;
			free(e);
			list->head = prev;
			return 1;
		}else if(e->value == value){
			prev->next = e->next;
			free(e);
			e = NULL;
			return 1;
		}
		prev = e;
		e = e->next;
	}
	return 0;
}


// Removes from the list and frees the nodes of all the items that are min <= value <= max
void sllist_remove_interval(SLList *list, int min, int max) {
	
	SLEntry * prev;
	SLEntry *e;
	e = list->head;
	prev = NULL;
	
	while(e != NULL){
		if((e->value >= min) && (e->value <= max) && (e == list->head)
		){
			prev = e->next;
			free(e);
			list->head = prev;
			e = list->head;
			
		}else if((e->value >= min) && (e->value <= max)){
			prev->next = e->next;
			free(e);
			e = prev->next;

		}
		else{
			prev = e;
			e = e->next;
		}
	}
	
}


// It allocates and returns a new list with the intersection of the two lists, that is the 
// list of all the items that are common to the two lists. The items in the intersection are
// unique. 
SLList *
sllist_intersection(SLList *a, SLList *b) {
	SLEntry *e1;
	e1 = a->head;
	SLEntry *e2;
	e2 = b->head;




/*
	while(e1!= NULL){
		printf("%d\n",e1->value);
		e1 = e1->next;
	}
	while(e2!= NULL){
		e2 = e2->next;
		printf("%d\n",e2->value);
	}
*/


	//create new list.
	SLList *result;
	SLEntry *eresult;
	eresult = result->head;
	// check list a,b
	SLEntry *testa;
	testa = a->head;
	SLEntry *testb;
	testb = b->head;
	while(testb != NULL){
	//	printf("list a has:%d\n",testa->value);
		testb = testb->next;
	}




	//check if a or b is empty, return NULL
	if(e1 == NULL || e2 == NULL){
		return NULL;
	}else{
		while(e1 != NULL){
			while(e2 != NULL){
				if(e1->value == e2->value){
					eresult = (SLEntry *)malloc(sizeof(SLEntry));
					eresult->value = e2->value;
					eresult = eresult->next;
				}	
				e2 = e2->next;
			}
			e2 = b->head;
			e1 = e1->next;
		}
		return result;
	}


/*
	//test print new list
	SLEntry *test;
	test = result->head;
	while(test != NULL){
	//	printf("test = %d\n", test->value);
		test = test->next;
	}
*/
//	return result;
}

void
sllist_print(SLList *list)
{
	// Move to the end
	SLEntry * e = list->head;

	printf("--- List ---\n");
	while (e!= NULL) {
		printf("val=%d\n", e->value);
		e = e->next;
	}
}
//rds cosmos.txt               : 0   of 15 
