#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "review.h"

void llist_init( List * list ) {
    list->head = NULL;
}

void llist_print( List * list ) {
    printf("Printing List...\n");
    if (list->head == NULL) {
	printf("{Empty}\n");
	return;
    }
    ListNode *e = list->head;
    while ( e->next != NULL ) {
	printf("%d->", e->value);
	e = e->next;
    }
    printf("%d\n", e->value);
}

void llist_clear( List * list ) {
    while ( list->head != NULL ) {
	ListNode *e = list->head->next;
	free(list->head);
	list->head = e;
    }
}

void test1() {
    char * s1 = strdup("helios");
    char * s2 = strdup("hello");
    size_t n = 4;
    int ret = strncmp(s1, s2, n);
    printf("strncmp(\"%s\", \"%s\", %zu)=%d\n", s1, s2, n, ret);

    n = 3;
    ret = strncmp(s1, s2, n);
    printf("strncmp(\"%s\", \"%s\", %zu)=%d\n", s1, s2, n, ret);
    free(s1);
    free(s2);

    s1 = strdup("b");
    s2 = strdup("a");
    n = 1;
    ret = strncmp(s1, s2, n);
    printf("strncmp(\"%s\", \"%s\", %zu)=%d\n", s1, s2, n, ret);
    free(s1);
    free(s2);
}

void test2() {
    char * s1 = strdup("blackout");
    char * s2 = strdup("blast");
    size_t n = 5;
    int ret = strncmp(s1, s2, n);
    printf("strncmp(\"%s\", \"%s\", %zu)=%d\n", s1, s2, n, ret);

    ret = strncmp(s2, s1, n);
    printf("strncmp(\"%s\", \"%s\", %zu)=%d\n", s2, s1, n, ret);

    n = 3;
    ret = strncmp(s2, s1, n);
    printf("strncmp(\"%s\", \"%s\", %zu)=%d\n", s2, s1, n, ret);

    free(s1);
    free(s2);
}

void test3() {
    int array [] = {34, 12, 45, 4};
    int n = sizeof(array)/sizeof(int);
    int sub_n = 2;

    int * small_elements = sub_min_array( array, n, sub_n );

    printf("array = {34, 12, 45, 4}\n");
    printf("sub array size = %d\n", sub_n);
    printf("min sub array = {");
    for (int i = 0; i < sub_n - 1; ++i) {
	printf("%d, ", small_elements[i]);
    }
    printf("%d}\n", small_elements[sub_n - 1]);

    free(small_elements);
}

void test4() {
    int array [] = {2, 35, 83, 21, 93, 23};
    int n = sizeof(array)/sizeof(int);
    int sub_n = 3;

    int * small_elements = sub_min_array( array, n, sub_n );

    printf("array = {2, 35, 83, 21, 93, 23}\n");
    printf("sub array size = %d\n", sub_n);
    printf("min sub array = {");
    for (int i = 0; i < sub_n - 1; ++i) {
	printf("%d, ", small_elements[i]);
    }
    printf("%d}\n", small_elements[sub_n - 1]);

    free(small_elements);

    puts("");

    // Wagstaff primes
    int array2 [] = {3, 11, 43, 683, 2731, 43691, 174763, 2796203};
    n = sizeof(array)/sizeof(int);
    sub_n = 5;
    small_elements = sub_min_array( array2, n, sub_n );

    printf("array = {3, 11, 43, 683, 2731, 43691, 174763, 2796203}\n");
    printf("sub array size = %d\n", sub_n);
    printf("min sub array = {");
    for (int i = 0; i < sub_n - 1; ++i) {
	printf("%d, ", small_elements[i]);
    }
    printf("%d}\n", small_elements[sub_n - 1]);

    free(small_elements);
}

void test5() {
    unsigned int x = 255;
    printf("print_bits(%d)\n", x);
    print_bits( x );

    x = 5;
    printf("print_bits(%d)\n", x);
    print_bits( x );
}

void test6() {
    unsigned int x = 0x532A;
    printf("print_bits(%d)\n", x);
    print_bits( x );

    x = 0x1738;
    printf("print_bits(%d)\n", x);
    print_bits( x );
}

void test7() {
    List list;
    llist_init( &list );
    llist_insert_last( &list , 4 );
    llist_insert_last( &list , 2 );
    llist_insert_last( &list , 9 );
    llist_insert_last( &list , 8 );
    llist_insert_last( &list , 13 );
    llist_print( &list );
    
    llist_clear( &list );
}

void test8() {
    List list;
    llist_init( &list );
    llist_insert_last( &list , 5 );
    llist_insert_last( &list , 4 );
    llist_insert_last( &list , 3 );
    llist_insert_last( &list , 2 );
    llist_insert_last( &list , 1 );
    llist_print( &list );

    puts("");

    List list2;
    llist_init( &list2 );
    llist_insert_last( &list2 , 815 );
    llist_insert_last( &list2 , 434 );
    llist_print( &list2 );

    puts("");

    List list3;
    llist_init( &list3 );
    llist_insert_last( &list3 , 1 );
    llist_print( &list3 );

    puts("");

    llist_insert_last( &list, 0 );
    llist_print( &list );

    llist_clear( &list );
    llist_clear( &list2 );
    llist_clear( &list3 );
}

int main(int argc, char ** argv) {

    char * test;

    if (argc < 2) {
	printf("Usage: test_array test1|test2|test3|test4|test5|test6\n");
	exit(1);
    }

    test = argv[1];
    printf("Running %s\n", test);
    if (strcmp(test, "test1")==0) {
	test1();
    }
    else if (strcmp(test, "test2")==0) {
	test2();
    }
    else if (strcmp(test, "test3")==0) {
	test3();
    }
    else if (strcmp(test, "test4")==0) {
	test4();
    }
    else if (strcmp(test, "test5")==0) {
	test5();
    }
    else if (strcmp(test, "test6")==0) {
	test6();
    }
    else if (strcmp(test, "test7")==0) {
	test7();
    }
    else if (strcmp(test, "test8")==0) {
	test8();
    }
    else {
	printf("Test not found!\n");
	exit(1);
    }
}

