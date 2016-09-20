#ifndef REVIEW_H
#define REVIEW_H

// ListNode of single linked list
typedef struct ListNode {
    int value;
    struct ListNode * next;
} ListNode;

// Single Linked List
typedef struct List {
    ListNode * head;
} List;

// Function Declerations
extern int strncmp( const char * s1, const char * s2, size_t n );
int * sub_min_array( int * array, int n, int sub_n );
void print_bits ( unsigned int x );
void llist_init( List * list );
void llist_print( List * list );
void llist_insert_last( List * list, int value );
void llist_clear( List * list );

#endif
