
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "resizable_table.h"

//
// It returns a new RESIZABLE_TABLE. It allocates it dynamically,
// and initializaes the values. The initial maximum size of the array is 10.
//
RESIZABLE_TABLE * rtable_create() {

	// Allocate a RESIZABLE_TABLE
	RESIZABLE_TABLE * table = (RESIZABLE_TABLE *) malloc(sizeof(RESIZABLE_TABLE));
	if (table == NULL) {
		return NULL;
	}
	
	// Initialze the members of RESIZABLE_TABLE
	table->maxElements = INITIAL_SIZE_RESIZABLE_TABLE;
	table->currentElements = 0;
	table->array = (struct RESIZABLE_TABLE_ENTRY *)
		malloc(table->maxElements*sizeof(RESIZABLE_TABLE_ENTRY));
	if (table->array==NULL) {
		return NULL;
	}
	
	return table;
}

//
// It prints the elements in the array assuming the value is a string in the form:
//
//======== Table =======
//currentElements=2 maxElements=10
//0: "George"       "23 Oak St, West Lafayette, 47906"
//1: "Peter"        "27 Oak St, West Lafayette, 47906"
//======== End Table =======
//
void rtable_print_str(RESIZABLE_TABLE * table)
{
	int i = 0;
	printf("\n======== Table =======\n");
	printf("currentElements=%d maxElements=%d\n", table->currentElements, table->maxElements);
	for (i=0; i<table->currentElements; i++) {
		printf("%d: \"%s\" \"%s\"\n", i, table->array[i].name, (char*) table->array[i].value);
	}
	printf("======== End Table =======\n");
	return;
}

//
// It prints the elements in the array assuming the value is an int:
//
//======== Table =======
//currentElements=2 maxElements=10
//0: "George"               101
//1: "Peter"                245
//======== End Table =======
//
void rtable_print_int(RESIZABLE_TABLE * table)
{
	int i = 0;
	printf("\n======== Table =======\n");
	printf("currentElements=%d maxElements=%d\n", table->currentElements, table->maxElements);
	for (i=0; i<table->currentElements; i++) {
		printf("%d: \"%s\" %ld\n", i, table->array[i].name, (long) table->array[i].value);
	}
	printf("======== End Table =======\n");
	return;
}

//
// Adds one pair name/value to the table. If the name already exists it will
// Substitute its value. Otherwise, it will store name/value in a new entry.
// If the new entry does not fit, it will double the size of the array.
// The name string is duplicated with strdup() before assigning it to the
// table.
//
int rtable_add(RESIZABLE_TABLE * table, char * name, void * value) {

// Find if it is already there and substitute value
	int scan = 0;
	while (table->array[scan].name != '\0') {
		if (!strcmp(table->array[scan].name, name)) {
			table->array[scan].value = value;
			return 0;
		}
		scan ++;
		
	}
	// If we are here is because the entry was not found.
	
	// Make sure that there is enough space
	if(table->currentElements >= table->maxElements){
		table->maxElements = 2 * table->maxElements;
		struct RESIZABLE_TABLE_ENTRY * jnx;
		jnx = table->array;


		table->array = (struct RESIZABLE_TABLE_ENTRY *)
			malloc(table->maxElements*sizeof(RESIZABLE_TABLE_ENTRY));
		memcpy(table->array, jnx, table->maxElements/2*sizeof(RESIZABLE_TABLE_ENTRY));
	}
		

	// Add name and value to a new entry.
	table->array[table->currentElements].name = strdup(name);
	table->array[table->currentElements].value = value;
	table->currentElements++;
	// We need to use strdup to create a copy of the name but not value.
	//
	
	return 0;
}

//
// Add name and value into table where value is a string (char *)
// Implement on top of rtable_add.
//
int rtable_add_str(RESIZABLE_TABLE * table, char * name, char * str_value)
{
	return rtable_add(table, name, (void *) strdup(str_value));
}

//
// Add name and value into table where value is a long
// Implement on top of rtable_add.
//
int rtable_add_int(RESIZABLE_TABLE * table, char * name, long int_value)
{
	return rtable_add(table, name, (void *) int_value );
}

//
// Returns the value that correspond to the name or NULL if the
// name does not exist in the table.
//
void * rtable_lookup(RESIZABLE_TABLE * table, char * name) {
	int i = 0;
        for (i; table->currentElements; i++) {
		if(!(strcmp(table->array[i].name, name))) {
			return table->array[i].value;
		}
	}
	return NULL;

}

//
// It removes the entry with that name from the table. The entries after the entry
// removed will shift downwards. Also the name and value strings will be freed.
//
int rtable_remove(RESIZABLE_TABLE * table, char * name) {
	int i = 0;
	while (table->currentElements > i) {
		if (!(strcmp(table->array[i].name, name))) {
			while(table->currentElements > i) {
				table->array[i] = table->array[i + 1];
				i++;
				
			}	
			table->currentElements--;
			return 1;
		}
		
		i++;
	}
	return 0;
}

//
// It returns in *name and *value the name and value that correspond to
// the ith entry. It will return 1 if successful, or 0 otherwise.
//
int rtable_get_ith(RESIZABLE_TABLE * table, int ith, char ** name, void ** value) {
	if (ith < table->currentElements) {
		* name = table->array[ith].name;
		* value = table->array[ith].value;
		return 1;
	}
	else {
		return 0;
	}
}

//
// It removes the ith entry from the table. The entries after the entry removed are
// moved downwards to use the empty space. Also the name/value strings are freed.
//
int rtable_remove_ith(RESIZABLE_TABLE * table, int ith) {
	int i = ith;
	if (i < table->currentElements){
		while(table->currentElements > i) {
			table->array[i] = table->array[i + 1];
			i++;
		}
		table->currentElements --;
		return 1;
	}	

	return 0;
}

//
// It returns the number of elements in the table.
//
int rtable_number_elements(RESIZABLE_TABLE * table) {
	return table->currentElements;
}

//
// It returns the maximum number of elements in the table
//
int rtable_max_elements(RESIZABLE_TABLE * table) {
	return table->maxElements;
}

#define MAXLINE 512

//
// It saves the table in a file called file_name with values as char *. The format of the
// file is as follows:
//
// name1\n
// str1\n
// \n
// name2\n
// str2\n
// ...
//
// Notice that there is an empty line between each name/value pair.
//
int rtable_save_str(RESIZABLE_TABLE * table, char * file_name) {
	FILE * fp;
	int i = 0;
	fp = fopen(file_name,"w");

	if(fp == NULL){
		return 0;
	}
	else{
		while(table->currentElements > i){
			fprintf(fp,"%s\n",table->array[i].name);
			fprintf(fp,"%s\n",table->array[i].value);
			fprintf(fp,"\n");
			i++;
		}
	
	}
	fclose(fp);
	return 1;
}

//
// It reads the table from the file_name indicated asumiing that the values are
// char *. If the table already has entries, it will clear the entries.
//
int rtable_read_str(RESIZABLE_TABLE * table, char * file_name) {
	FILE * fp;
	int i = 0;
	fp = fopen(file_name, "r");

	if(fp == NULL) {
		return 0;
	}
	else{
		while (!feof(fp)) {
			char name [150];
			char value [150];
			char empty [150];
			fgets(name, 150, fp);
			fgets(value, 150, fp);
			fgets(empty, 150, fp);
			char *name2 = malloc(150);
			char *value2 = malloc(150);
			strncpy(name2,name,strlen(name) -1);
			strncpy(value2,value,strlen(value)-1);
			rtable_add_str(table, name2, value2);
		}
		
	}
	fclose(fp);

	return 1;
}

//
// It saves the table in a file called file_name with values as int. The format of the
// file is as follows:
//
// name1\n
// int1\n
// \n
// name2\n
// int2\n
// ...
//
// Notice that there is an empty line between each name/value pair.
//
int rtable_save_int(RESIZABLE_TABLE * table, char * file_name) {
	FILE * fp;
	int i = 0;
	fp = fopen(file_name,"w");
	if(fp == NULL){
		return 0;
	}
	else{
		while(i < table->currentElements){
			fprintf(fp,"%s\n",table->array[i].name);
			fprintf(fp,"%d\n",(int)table->array[i].value);
			fprintf(fp,"\n");
			i++;
		}
	}								
	fclose(fp);
	return 1;

}

//
// It reads the table from the file_name indicated asumiing that the values are
// char *. If the table already has entries, it will clear the entries.
//
int rtable_read_int(RESIZABLE_TABLE * table, char * file_name) {
	   FILE * fp;
	   //int i = 0;
	   fp = fopen(file_name, "r");
	   if(fp == NULL) {
	  	 return 0;
	   }
	   else{
	  	 while (!feof(fp)) {
	  		 char name [150];
	  		 char value [150];
	  		 char empty [150];
	  		 fgets(name, 150, fp);
	  		 fgets(value, 150, fp);
	  		 fgets(empty, 150, fp);
	 	  	 char *name2 = malloc(150);
	  		 char *value2 = malloc(150);
	  		 strncpy(name2,name,strlen(name) -1);
	  		 strncpy(value2,value,strlen(value)-1);
			 int value3;
			 value3 = atoi(value);
	  		 rtable_add_int(table, name2, value3);
	  	 }
	}
	fclose(fp);
	return 1;
}

//
// It sorts the table according to the name. The parameter ascending determines if the
// order si ascending (1) or descending(0).
//
void rtable_sort(RESIZABLE_TABLE * table, int ascending){
	int i = 0;
	int j = 1;
	struct RESIZABLE_TABLE_ENTRY * ls = malloc(sizeof(RESIZABLE_TABLE_ENTRY));
	if(ascending) {
	for (i; i < table->currentElements - 1; i++) {
		for(j = i+1; j < table->currentElements; j++) {
			if(strcmp(table->array[i].name, table->array[j].name)>0) {
				*ls = table->array[i];
				table->array[i] = table->array[j];
				table->array[j] = *ls;
			}
		}
	}
	}
	else {
		for (i; i < table->currentElements - 1; i++) {
			for(j = i+1; j < table->currentElements; j++) {
				if(strcmp(table->array[i].name, table->array[j].name)<0) {
					*ls = table->array[i];
					 table->array[i] = table->array[j];
					 table->array[j] = *ls;
				}

			}
		}
	}
}
//
// It sorts the table according to the name. The parameter ascending determines if the
// order si ascending (1) or descending(0).
//
void rtable_sort_by_intval(RESIZABLE_TABLE * table, int ascending)
{
}

//
// It removes the first entry in the table.
// All entries are moved down one position.
// It also frees memory allocated for name and value.
//
int rtable_remove_first(RESIZABLE_TABLE * table) {
	int i = 0;
	if (i < table->currentElements){
		while(table->currentElements > i) {
			table->array[i] = table->array[i + 1];
			i++;
		}
		table->currentElements --;
		return 1;
	}
	return 0;
}

//
// It removes the last entry in the table.
// It also frees memory allocated for name and value.
//
int rtable_remove_last(RESIZABLE_TABLE * table) {
	int i = 0;
	if(i < table->currentElements){
		i = table->currentElements;
		//free(table->array[i]);
		table->currentElements--;
		return 1;
	}
	return 0;
}

//
// Insert a name/value pair at the beginning of the table.
// The entries are moved one position upwards.
// There is no check if the name already exists. The entry is added
// at the beginning of the table.
//
int rtable_insert_first(RESIZABLE_TABLE * table, char *name, void * value) {
	if (table->currentElements == table->maxElements) {
		table->maxElements = 2 * table->maxElements;
 		struct RESIZABLE_TABLE_ENTRY * jnx;
                jnx = table->array;
		table->array = (struct RESIZABLE_TABLE_ENTRY *)
			malloc(table->maxElements*sizeof(RESIZABLE_TABLE_ENTRY));
		memcpy(table->array, jnx, table->maxElements/2*sizeof(RESIZABLE_TABLE_ENTRY));
		int i = table->currentElements - 1;
		for (i ; i >= 0 ; i-- ) {
			table->array[i + 1] = table->array[i];
		}
		
	table->array[0].name = strdup(name);
	table->array[0].value = value;
	table->currentElements++;

	}
	else{
		int j = table->currentElements - 1;
	        for (j ; j >= 0 ; j-- ) {
			table->array[j + 1] = table->array[j];

		}

	table->array[0].name = strdup(name);
	table->array[0].value = strdup(value);
	table->currentElements++;
	}
	return 1;
}

//
// Insert a name/value pair at the end of the table.
// The entries are moved one position upwards.
// There is no check if the name already exists. The entry is added
// at the end of the table.
//
int rtable_insert_last(RESIZABLE_TABLE * table, char *name, void * value) {
	if (table->currentElements == table->maxElements) {
		table->maxElements = 2 * table->maxElements;
		struct RESIZABLE_TABLE_ENTRY * jnx;
		jnx = table->array;
		table->array = (struct RESIZABLE_TABLE_ENTRY *)
		malloc(table->maxElements*sizeof(RESIZABLE_TABLE_ENTRY));
		memcpy(table->array, jnx, table->maxElements/2*sizeof(RESIZABLE_TABLE_ENTRY));

	}
	table->array[table->currentElements].name = strdup( name);
	table->array[table->currentElements].value = value;
	table->currentElements++;
	return 0;
}

