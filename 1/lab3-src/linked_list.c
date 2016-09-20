
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"

//
// It returns a new LINKED_LIST. It allocates it dynamically,
// and initializaes the values. The initial list is empty.
//
LINKED_LIST * llist_create() {

	LINKED_LIST * list = (LINKED_LIST *) malloc(sizeof(LINKED_LIST));
	if (list == NULL) {
		return NULL;
	}

	// Create Sentinel node. This node does not store any data
	// but simplifies the list implementation.
	list->head = (LINKED_LIST_ENTRY *) malloc(sizeof(LINKED_LIST_ENTRY));
	if (list->head == NULL) {
		return NULL;
	}
	
	
	list->nElements = 0;
	list->head->next = list->head;
	list->head->previous = list->head;
	
	return list;
}

//
// It prints the elements in the alist in the form:
//
//===== List =====
//currentElements=2 maxElements=10
//0: Name: "George"       "23 Oak St, West Lafayette, 47906"
//1: Name: "Peter"        "27 Oak St, West Lafayette, 47906"
//======== End List =======
//
void llist_print(LINKED_LIST * list) {
	
	LINKED_LIST_ENTRY * e;

	printf("===== List =====\n");
	printf("nElements=%d\n", list->nElements);

	e = list->head->next;
	while (e != list->head) {
		printf("name=\"%s\" value=\"%s\"\n", e->name, e->value);
		e = e->next;
	}
	printf("======== End List =======\n");
}

//
// Adds one pair name/value to the list. If the name already exists it will
// Substitute its value. Otherwise, it will store name/value in a new entry.
// The name/vale strings are duplicated with strdup() before adding them to the
// list.
//
int llist_add(LINKED_LIST * list, char * name, char * value) {
	LINKED_LIST_ENTRY * e;

	e = list->head->next;
	while(e != list->head){
		if(!strcmp(e->name, name)) {
			e->value = strdup(value);
		return 0;
		}
		e = e->next;
	}
	e = (LINKED_LIST_ENTRY *) malloc (sizeof(LINKED_LIST_ENTRY));
	e->name = strdup(name);
	e->value = strdup(value);
	e->next = list->head;
	e->previous = list->head->previous;
	e->previous->next = e;
	list->head->previous = e;
	list->nElements++;
	return 0;

}

//
// Returns the value that correspond to the name or NULL if the
// name does not exist in the list.
//
char * llist_lookup(LINKED_LIST * list, char * name) {
	LINKED_LIST_ENTRY *e;
	e=list->head->next;
	while(e != list->head) {
		if(!strcmp(e->name,name)) {
			return e->value;
		}
		e = e->next;
	}
	return NULL;
}

//
// It removes the entry with that name from the list.
// Also the name and value strings will be freed.
//
int llist_remove(LINKED_LIST * list, char * name) {
	LINKED_LIST_ENTRY *e;
	e = list->head->next;

	while (e != list->head){
		if (!(strcmp(e->name, name))){
			e->previous->next = e->next;
			e->next->previous = e->previous;
			list->nElements--;
			return 1;
		}
		e = e->next;
	}
	return 0;
}

//
// It returns in *name and *value the name and value that correspond to
// the ith entry. It will return 1 if successful, or 0 otherwise.
//
int llist_get_ith(LINKED_LIST * list, int ith, char ** name, char ** value) {
	LINKED_LIST_ENTRY *e;
	e = list->head->next;
	int i = 0;

	if(ith < list->nElements){
		while (i < ith){
			i ++;
			e = e->next;
		}
		*name = e->name;
		*value = e->value;
		return 1;
	}
	else{
		return 0;
	}
}

//
// It removes the ith entry from the list.
// Also the name/value strings are freed.
//
int llist_remove_ith(LINKED_LIST * list, int ith) {
	LINKED_LIST_ENTRY *e;
	e = list->head->next;

	int i = 0;
	while(e != list->head){
		if (i == ith){
			e->previous->next = e->next;
			e->next->previous = e->previous;
			list->nElements --;
			return 1;
		}
		else{
			e = e->next;
			i++;
		}
		
	}
	return 0;
}

//
// It returns the number of elements in the list.
//
int llist_number_elements(LINKED_LIST * list) {
	return list->nElements;
}


//
// It saves the list in a file called file_name. The format of the
// file is as follows:
//
// name1\n
// value1\n
// \n
// name2\n
// value2\n
// ...
//
// Notice that there is an empty line between each name/value pair.
//
int llist_save(LINKED_LIST * list, char * file_name) {
	LINKED_LIST_ENTRY *e;
	e = list->head->next;
	FILE * fp;
	int i = 0;
	fp = fopen(file_name, "w");

	if(fp == NULL) {
		return 0;
	}
	else {
		while(e != list->head) {
			fprintf(fp, "%s\n", e->name);
			fprintf(fp, "%s\n", e->value);
			fprintf(fp, "\n");
			e = e->next;
		
		}
		
	}
	fclose(fp);
	return 1;

}

//
// It reads the list from the file_name indicated. If the list already has entries, it will
// clear the entries.
//
int llist_read(LINKED_LIST * list, char * file_name) {
	LINKED_LIST_ENTRY *e;
	e = list->head->next;
	FILE *fp;
	int i = 0;
	fp = fopen(file_name, "r");

	if(fp == NULL) {
		return 0;
	}
	else {
		while(!feof(fp)) {
			char name [150];
			char value [150];
			char empty [150];
			fgets(name,150,fp);
			fgets(value,150,fp);
			fgets(empty,150,fp);
			char *name2 = malloc(150);
			char *value2 = malloc(150);
			strncpy(value2, value, strlen(value) - 1);
			strncpy(name2, name, strlen(name) - 1);
			llist_add(list, name2, value2);
			
		
		}
	}
	fclose(fp);
	return 1;
}

//
// It sorts the list according to the name. The parameter ascending determines if the
// order si ascending (1) or descending(0).
//
void llist_sort(LINKED_LIST * list, int ascending) {
	LINKED_LIST_ENTRY *e;
	LINKED_LIST_ENTRY *f;
	e = list->head->next;
	char * namesave;
	char * valuesave;
	if(ascending) {
		while(e != list->head) {
			f = e->next;
			while(f != list->head){
				if(strcmp(e->name, f->name)>0){
					namesave = f->name;
					valuesave = f->value;
					f->name = e->name;
					f->value = e->value;
					e->name = namesave;
					e->value = valuesave;
				}
				f = f->next;
			}
			e = e->next;
		}
	}
	else{
		while(e != list->head) {
			 f = e->next;
			 while(f != list->head){
				 if(strcmp(e->name, f->name) < 0){
					 namesave = f->name;
					 valuesave = f->value;
					 f->name = e->name;					
					 f->value = e->value;
					 e->name = namesave;
					 e->value = valuesave;
			 	}
			 	f = f->next;
			 }
		 	e = e->next;
		}

	}
}

//
// It removes the first entry in the list.
// All entries are moved down one position.
// It also frees memory allocated for name and value.
//
int llist_remove_first(LINKED_LIST * list) {
	LINKED_LIST_ENTRY *e;
	e = list->head->next;
	if(list->nElements >= 1){
		e->previous->next = e->next;
		e->next->previous = list->head;
		list->nElements--;
		return 1;
	}
//	else if(list->nElements = 1){
//		e->next->next = list->head;
//		e->previous->previous = list->head;
//		list->nElements--;
//		return 1;
//	}
	else{
		return 0;
	}
}

//
// It removes the last entry in the list
// It also frees memory allocated for name and value.
//
int llist_remove_last(LINKED_LIST * list) {
	LINKED_LIST_ENTRY *e;
	e = list->head->previous;
	if(list->nElements >= 1) {
		e->previous->next = list->head;
		e->next->previous = e->previous;
		list->nElements--;
		return 1;
	}
/*	else if(list->nElements = 1){
		e->next->next = list->head;
		e->previous->previous = list->head;
		list->nElements--;
		return 1;
	}*/
	else {
		return 0;
	}
}

//
// Insert a name/value pair at the beginning of the list.
// There is no check if the name already exists. The entry is added
// at the beginning of the list.
//
int llist_insert_first(LINKED_LIST * list, char *name, char * value) {
	LINKED_LIST_ENTRY *e;
	e = list->head->next;
	e = (LINKED_LIST_ENTRY *) malloc (sizeof(LINKED_LIST_ENTRY));
	e->value = strdup(value);
	e->name = strdup(name);
	if(list->nElements >= 1){
		e->next = list->head->next;
		e->previous = list->head;
		list->head->next = e;
		list->head->next->previous = e;
	}
	else{
		e->previous = list->head;
		e->next = list->head->next;
		e->next->previous = e;
		list->head->next = e;
	}

	list->nElements++;
	return 1;

}

//
// Insert a name/value pair at the end of the list.
// There is no check if the name already exists. The entry is added
// at the end of the list.
//
int llist_insert_last(LINKED_LIST * list, char *name, char * value) {
	LINKED_LIST_ENTRY *e;
	e = list->head->next;
	e = (LINKED_LIST_ENTRY *) malloc (sizeof(LINKED_LIST_ENTRY));
	e->value = strdup(value);
	e->name = strdup(name);
	if(list->nElements >=1){
		e->next = list->head;
		e->previous = list->head->previous;
		list->head->previous->next = e;

		list->head->previous = e;
	}
	else{
		e->next = list->head;
		e->previous = list->head->previous;
		e->previous->next = e;
		list->head->previous = e;
	}
	list->nElements++;
	return 1;
}

