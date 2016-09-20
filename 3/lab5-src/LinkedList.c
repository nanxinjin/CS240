
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"
#include "nextword.h"
//
// Initialize a linked list
//
void llist_init(LinkedList * list)
{
	list->head = NULL;
}

//
// It prints the elements in the list in the form:
// 4, 6, 2, 3, 8,7
//
void llist_print(LinkedList * list) {
	
	ListNode * e;

	if (list->head == NULL) {
		printf("{EMPTY}\n");
		return;
	}

	printf("{");

	e = list->head;
	while (e != NULL) {
		printf("%d", e->value);
		e = e->next;
		if (e!=NULL) {
			printf(", ");
		}
	}
	printf("}\n");
}

//
// Appends a new node with this value at the beginning of the list
//
void llist_add(LinkedList * list, int value) {
	// Create new node
	ListNode * n = (ListNode *) malloc(sizeof(ListNode));
	n->value = value;
	
	// Add at the beginning of the list
	n->next = list->head;
	list->head = n;
}

//
// Returns true if the value exists in the list.
//
int llist_exists(LinkedList * list, int value) {
	ListNode * e;
	e = list->head;
	while(e != NULL){
		if(e->value == value){
			return 1;
		}
		e = e->next;
	}
	return 0;
}

//
// It removes the entry with that value in the list.
//
int llist_remove(LinkedList * list, int value) {
	ListNode * e1;
	ListNode * e2;
	e1 = list->head;
	e2 = list->head->next;
	if(e1->value == value){
		list->head = e2;
		return 1;
	}else{
		while(e2 != NULL){
			if(e2->value == value){
				e1->next = e2->next;
				return 1;
			}
			e1 = e1->next;
			e2 = e2->next;
		}
	}

	
	return 0;
}

//
// It stores in *value the value that correspond to the ith entry.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_get_ith(LinkedList * list, int ith, int * value) {
	ListNode * e;
	
	e = list->head;
	int i = 0;
	for(i;i<ith;i++){
		if(e == NULL){
			return 0;
		}
		e = e->next;
	}
	*value = e->value;

	return 1;;
}

//
// It removes the ith entry from the list.
// It returns 1 if success or 0 if there is no ith entry.
//
int llist_remove_ith(LinkedList * list, int ith) {
	ListNode * e1;
	ListNode * e2;
	int i = 1;

	e1 = list->head;
	e2 = list->head->next;

	if(ith == 0){
		list->head = e2;
		return 1;
	}else{
		for(i;i<ith;i++){
			if(e2 == NULL){
				return 0;
			}
			e1 = e1->next;
			e2 = e2->next;
		}
		e1->next = e2->next;
		return 1;

	}

}

//
// It returns the number of elements in the list.
//
int llist_number_elements(LinkedList * list) {
	int i = 0;
	ListNode * e;
	e = list->head;
	while(e != NULL){
		e = e->next;
		i++;
	}
	return i;
}


//
// It saves the list in a file called file_name. The format of the
// file is as follows:
//
// value1\n
// value2\n
// ...
//
int llist_save(LinkedList * list, char * file_name) {
	ListNode * e;
	e = list->head;
	int i = 0;
	FILE *fp;
	fp = fopen(file_name,"w");
	if(fp == NULL){
		return 0;
	}else{
		while(e != NULL){
			fprintf(fp,"%d\n",e->value);
			e = e->next;
		}
	}
	fclose(fp);
	return 0;
}

//
// It reads the list from the file_name indicated. If the list already has entries, 
// it will clear the entries.
//
int llist_read(LinkedList * list, char * file_name) {
	ListNode * e;
	e = list->head;
	if(e != NULL){
		llist_clear(list);
	}
	FILE *fp;
	fp = fopen(file_name,"w");
	char * c;
	if(fp == NULL){
		return 0;
	}else{
		while((c = nextword(fp)) != NULL){
			int temp = atoi(c);
			e->value = temp;
			e = e->next;
		}
	}
	
	
	fclose(fp);

	return 1;
}


//
// It sorts the list. The parameter ascending determines if the
// order si ascending (1) or descending(0).
//
void llist_sort(LinkedList * list, int ascending) {
	ListNode * e;
	e = list->head;
	ListNode * e1;
	e1 = e;
	int temp;
	int flag = 1;
	
	if(ascending){
	  while(e != NULL){
			while(e1 != NULL){
				if(e1->value > e->value){
					temp = e1->value;
					e1->value = e->value;
					e->value = temp;
				}
				e1 = e1->next;
			}
			
			e = e->next;

			e1 = e;
			
		}
	}else{
		while(e != NULL){
			while(e1 != NULL){
				if(e1->value < e->value){
					temp = e1->value;
					e1->value = e->value;
					e->value = temp;
				}
				e1 = e1->next;
			}
			 e = e->next;
			 e1 = e;
		}
	}
	
}

//
// It removes the first entry in the list and puts value in *value.
// It also frees memory allocated for the node
//
int llist_remove_first(LinkedList * list, int * value) {
	ListNode * e;
	e = list->head;
	if(e == NULL){
		return 0;
	}else{
		*value = e->value;
	}
	list->head = e->next;
	free(e);
	return 1;
	
}

//
// It removes the last entry in the list and puts value in *value/
// It also frees memory allocated for node.
//
int llist_remove_last(LinkedList * list, int *value) {
	ListNode * e;
	ListNode * e1;
	e = list->head;
	e1 = NULL;
	if(e == NULL){
		return 0;
	}else{
		while(e->next != NULL){
			e1 = e;;
			e = e->next;
		}
	}
	*value = e->value;
	e1->next = e->next;
	free(e);
  	return 1;
}

//
// Insert a value at the beginning of the list.
// There is no check if the value exists. The entry is added
// at the beginning of the list.
//
void llist_insert_first(LinkedList * list, int value) {
	ListNode * e1;
	ListNode * e;
	e1 = NULL;
	e = list->head;
	if(e == NULL){
		e = (ListNode *) malloc(sizeof(ListNode));
		e->value = value;
		list->head = e;
	}else{
		e1 = (ListNode *) malloc(sizeof(ListNode));
		list->head = e1;
		e1->value = value;
		e1->next = e;
	}

}

//
// Insert a value at the end of the list.
// There is no check if the name already exists. The entry is added
// at the end of the list.
//
void llist_insert_last(LinkedList * list, int value) {
	ListNode *e1;
	e1 = NULL;
	ListNode * e;
	e = list->head;
	if(e == NULL){
		e = (ListNode *) malloc(sizeof(ListNode));
		e->value = value;
		e->next = NULL;
		list->head = e;
	}else{
		while(e != NULL){
			e1 = e;
			e = e->next;
		}
		e = (ListNode *) malloc(sizeof(ListNode));
		e->value = value;
		e->next = NULL;
		e1->next = e;
	}

}

//
// Clear all elements in the list and free the nodes
//
void llist_clear(LinkedList *list)
{
	ListNode *e;
	ListNode * e1;
	e1 = NULL;
	e = list->head;
	if(e == NULL){
		free(e);
	}else{
		while(e != NULL){
			e1 = e;
			e = e->next;
			e1 = NULL;
			free(e1);
		}
		list->head = e;
	}
}
