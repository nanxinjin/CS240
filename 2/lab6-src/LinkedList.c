
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LinkedList.h"

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
		printf("%s %s", e->name,e->password);
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
void llist_add(LinkedList * list, const char* name,const char*password) {
	// Create new node
	if(llist_exists(list,name,password) == 0){
		ListNode * n = (ListNode *) malloc(sizeof(ListNode));
		n->name = strdup(name);
		n->password = strdup(password);
	// Add at the beginning of the list
		n->next = list->head;
		list->head = n;
	}
}

//
// Returns true if the value exists in the list.
//
int llist_exists(LinkedList * list, const char* name, const char*password) {
	ListNode *e;
	e = list->head;
	while(e != NULL){
		if(!strcmp(e->name,name)){
			if(!strcmp(e->password,password)){
				return 1;

			}else{
				return 0;

			}
		}
		e = e->next;
	}
	return 0;
}

//
// It removes the entry with that value in the list.
//
int llist_remove(LinkedList * list,const char*name){
	ListNode *pre;
	ListNode *e;
	e = list->head;
	pre = NULL;
	while(e != NULL){
		if(strcmp(e->name,name) == 0){
			break;
		}
		pre=e;
		e=e->next;
	}
	int num;
	if(pre == NULL){
		num = 1;
	}else if(e == NULL){
		num = 2;
	}else{
		num  = 3;
	}

	switch(num){
		case 1:
			list->head = e->next;
		break;
		
		case 2:
			return 0;
		break;

		case 3:
			pre->next = e->next;
		break;

		default:
		break;
	}

	free(e);
	return 1;
}

int llist_remove_room(LinkedList * list,const char * name, const char * password){
        ListNode *pre;
	ListNode *e;
	e = list->head;
	pre = NULL;
	while(e != NULL){
		if(!strcmp(password , e->name)){
			if(!strcmp(name, e->password)){
				break;
			}
		}
		pre=e;
		e=e->next;
	}

	int num;
	if(pre == NULL){
		num = 1;
	}else if(e == NULL){
		num = 2;
	}else{
		num = 3;
	}
	switch(num){
		case 1:
			list->head = e->next;
			break;
		case 2:
			return 0;
			break;
		case 3:
			pre->next = e->next;
			break;
		default:
			break;
	}

	free(e);
	return 1;
}

//
// It stores in *value the value that correspond to the ith entry.
// It returns 1 if success or 0 if there is no ith entry.

/*
int llist_get_ith(LinkedList * list, int ith,char *name) {
	ListNode *e;
	e = list->head;
	int count = 0;
	while(e != NULL){
		for(count;count != ith; count ++){
		//check if list does not has ith elements, then return 0;
			if(e->next == NULL){
				return 0;
			}else{
				e = e->next;
			}
		}
		//store value to *value
		*name = e->name;
		return 1;
	}
}*/

//
// It removes the ith entry from the list.
// It returns 1 if success or 0 if there is no ith entry.
/*
int llist_remove_ith(LinkedList * list, int ith) {
	ListNode *e;
	ListNode *pre;
	e = list->head;
	pre = NULL;
	int count = 0;
	
	while(e != NULL){
		//if ith = 0, then remove head
		if(ith == 0){
			list->head = e->next;
			return 1;
		}

		for(count;count != ith; count++){
			//check if list does not has ith elements, then return 0;
			if(e->next == NULL){
				return 0;
			}else{ 
			//if ith element does exist, then let e move to ith node
				pre = e;
				e = e->next;
			}
		}
		//remove ith entry
		pre->next = e->next;
		free(e);
		e = NULL;
		return 1;
	}
}
*/
//
// It returns the number of elements in the list.
//
int llist_number_elements(LinkedList * list) {
	ListNode * e;
	e = list->head;
	int count = 0;;
	
	while(e != NULL){
		e = e->next;
		count ++;
	}
	return count;
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
	ListNode *e;
	e = list->head;
	int position = 0;
	FILE *fp;
	fp = fopen(file_name,"w");
	
	if(fp == NULL){
		return 0;
	}else{
		while (e != NULL){
			fprintf(fp,"%s %s\n",e->name,e->password);
			e = e->next;
		}
	}
	fclose(fp);

	return 1;
}

//
// It reads the list from the file_name indicated. If the list already has entries, 
// it will clear the entries.
//
int llist_read(LinkedList * list, char * file_name) {
	ListNode *e;
	e = list->head;
	FILE * fp;
	fp = fopen(file_name,"rw+");

	if(fp == NULL){
		return 0;
		while(!feof(fp)){
			if(!feof(fp)){
				char * name = (char*)malloc(1500*sizeof(char));
				char * password = (char*)malloc(1500*sizeof(char));
				fscanf(fp,"%s %s\n",(name),(password));
			//test
			//printf("This is test%d\n",store);
				llist_add(list,name,password);
			}	
		}
		fclose(fp);
		return 1;
	}
}


//
// It sorts the list. The parameter ascending determines if the
// order is ascending (1) or descending(0).
//
void llist_sort_ascend(LinkedList * list) {
	ListNode *e;
	e = list->head;
	char * tempName;
	char * tempPassword;
	int flag = 1;
	while(flag == 1){
		flag = 0;
		e = list->head;
		
		if(e->next == NULL || e == NULL){
			return;
		}else{
			while(e ->next){
				if(strcmp(e->name,e->next->name)>0){
					flag = 1;
					tempName = strdup(e->name);
					tempPassword = strdup(e->password);
					
					strcpy(e->name, e->next->name);
					strcpy(e->password,e->next->password);
					strcpy(e->next->name,tempName);
					strcpy(e->next->password,tempPassword);
				}
				e = e->next;
			}
		}
	}
}

void llist_sort_descend(LinkedList * list){
	ListNode *e;
	e = list->head;
	char * tempName;
	char * tempPassword;
	int flag = 1;
	while(flag == 1){
		flag = 0;
		e = list->head;
		if(e->next == NULL || e == NULL){
			return;
		}else{
			while(e ->next){
				if(strcmp(e->name,e->next->name)<0){
					flag = 1;
					tempName = strdup(e->name);
					tempPassword = strdup(e->password);
					strcpy(e->name, e->next->name);
					strcpy(e->password,e->next->password);
					strcpy(e->next->name,tempName);
					strcpy(e->next->password,tempPassword);
				}
				e = e->next;
			}		
		}	
	}

}


void llist_init_message(MessageList * list){
	list->head = NULL;
}

void llist_add_message(MessageList * list, const char* roomP, const char * userP, const char * messageP){
	MessageNode * n = (MessageNode *)malloc(sizeof(MessageNode));
	n->room = strdup(roomP);
	n->user = strdup(userP);
	n->message = strdup(messageP);
	n->next = list->head;
	list->head = n;
}
//
// It removes the first entry in the list and puts value in *value.
// It also frees memory allocated for the node
/*
int llist_remove_first(LinkedList * list, int * value) {
	ListNode *e;
	e = list->head;
	if(e == NULL){
		return 0;
	}else{
		*value = e->value;
	}
	list->head = e->next;
	free(e);
	//Test
	//printf("this is *value: %c\n",*value);
	return 1;
}
*/
//
// It removes the last entry in the list and puts value in *value/
// It also frees memory allocated for node.
//
/*
int llist_remove_last(LinkedList * list, int *value) {
	ListNode *e;
	ListNode *prev;
	prev = NULL;
	e = list->head;
	if(e == NULL){
		return 0;
	}else{
		while(e->next != NULL){
			prev = e;
			e = e->next;
		}
	}
	*value = e->value;
	prev->next = e->next;
	free(e);
	return 1;
}
*/
//
// Insert a value at the beginning of the list.
// There is no check if the value exists. The entry is added
// at the beginning of the list.
/*
void llist_insert_first(LinkedList * list, int value) {
	ListNode *e;
	ListNode *insert;
	insert = NULL;
	e = list->head;
	if(e == NULL){
		e = (ListNode*)malloc(sizeof(ListNode));
		e->value = value;
		list->head = e;
	}else{
		insert = (ListNode*)malloc(sizeof(ListNode));
		list->head = insert;
		insert->value = value;
		insert->next = e;
	}


}
*/
//
// Insert a value at the end of the list.
// There is no check if the name already exists. The entry is added
// at the end of the list.
/*
void llist_insert_last(LinkedList * list, int value) {
	ListNode *e;
	ListNode *insert;
	e = list->head;
	insert = NULL;
	if(e == NULL){
		e = (ListNode *)malloc(sizeof(ListNode));
		e->value = value;
		list->head = e;
	}else{
		while(e != NULL){
			insert = e;
			e = e->next;
		}
		e = (ListNode *)malloc(sizeof(ListNode));
		e->value = value;
		insert->next = e;
	}
}

*/
// Clear all elements in the list and free the nodes
/*
void llist_clear(LinkedList *list)
{
	ListNode *e;
	ListNode *prev;
	prev = NULL;
	e = list->head;
	if(e = NULL){
		free(e);
	}else{
		while(e != NULL){
			prev = e;
			e = e->next;
			prev = NULL;
			free(prev);
			
		}
		list->head = e;
	}	
}
*/
