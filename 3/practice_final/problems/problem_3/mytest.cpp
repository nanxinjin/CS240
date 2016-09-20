#include <string>
#include <stdlib.h>
#include <iostream>
#include "DLList.h"

int ListNode::node_count = 0;

void test1() {
    DLList list;
    list.insert_first( 9 );
    list.insert_first( 21 );
    list.insert_first( 8 );
    list.insert_first( 35 );
    list.insert_first( 3 );
    list.insert_first( 15 );
    list.print_list();
}

void test2() {
    DLList list1;
    list1.insert_first( 5 );
    list1.insert_first( 1 );
    list1.insert_first( 13 );
    list1.insert_first( 2 );
    list1.print_list("List1");

    std::cout << std::endl;

    DLList * list2 = new DLList();
    list2->insert_first( 38 );
    list2->print_list("List2");

    std::cout << std::endl;

    DLList * list3 = new DLList();
    list3->print_list("List3");

    delete list2;
    delete list3;
}

void test3() {
    DLList list;
    for (int i = 0; i < 10; i++) {
	list.insert_first( i );
    }
    list.print_list();
    std::cout << std::endl;

    bool b = list.remove( 8 );
    std::cout << "Removed 8: " << b << std::endl;
    list.print_list();
    std::cout << std::endl;

    b = list.remove( 11 );
    std::cout << "Removed 11: " << b << std::endl;
    list.print_list();
    std::cout << std::endl;

    b = list.remove( 3 );
    std::cout << "Removed 3: " << b << std::endl;
    list.print_list();
    std::cout << std::endl;

    b = list.remove( 73 );
    std::cout << "Removed 73: " << b << std::endl;
    list.print_list();
    std::cout << std::endl;

    b = list.remove( 1 );
    std::cout << "Removed 1: " << b << std::endl;
    list.print_list();
}

void test4() {
    DLList listA;
    for (int i = 4; i >= 0; i--) {
	listA.insert_first( i );
    }
    for (int i = 5; i >= -1; i--) {
	bool b = listA.remove( i );
	std::cout << "Removed " << i << ": " << b << std::endl;
	listA.print_list();
	if ( i != -1 )
	    std::cout << std::endl;
    }
}

void test5() {
    DLList * listA = new DLList();
    listA->insert_first( 8 );
    listA->insert_first( 1 );
    listA->insert_first( 7 );
    listA->print_list( "List A" );
    std::cout << std::endl;

    DLList * listB = new DLList();
    listB->insert_first( 34 );
    listB->insert_first( 2 );
    listB->insert_first( 4 );
    listB->print_list( "List B" );
    std::cout << std::endl;

    listA->concat_list( listB );
    listA->print_list( "List A concatenated with List B" );

    delete listA;
    delete listB;
}

void test6() {
    DLList * listA = new DLList();
    listA->insert_first( 1 );
    listA->insert_first( 3 );
    listA->insert_first( 2 );
    listA->print_list( "List A" );

    std::cout << std::endl;

    DLList * listB = new DLList();    
    listB->print_list( "List B" );

    std::cout << std::endl;

    listA->concat_list( listB );
    listA->print_list( "List A concatenated with List B" );

    delete listA;
    delete listB;
}

void test7() {
    DLList * listA = new DLList();
    listA->insert_first( 52 );
    listA->insert_first( 51 );
    listA->print_list( "List A" );
    DLList * listB = new DLList();
    for (int i = 50; i >= 0; i--) {
	listB->insert_first( i );
    }
    listB->print_list( "List B" );
    listB->concat_list( listA );
    listB->print_list( "List B concatenated with List A" );
    delete listA;
    delete listB;

    std::cout << std::endl;

    listA = new DLList();
    listA->insert_first( 52 );
    listA->insert_first( 51 );
    listA->print_list( "List A" );
    listB = new DLList();
    for (int i = 50; i >= 0; i--) {
	listB->insert_first( i );
    }
    listB->print_list( "List B" );
    listA->concat_list( listB );
    listA->print_list( "List A concatenated with List B" );
    delete listA;
    delete listB;
}

void test8() {
    // Test for memory leaks
    DLList * listA = new DLList();
    listA->insert_first( 2 );
    listA->insert_first( 3 );
    listA->insert_first( 5 );
    listA->insert_first( 7 );
    listA->insert_first( 11 );
    listA->insert_first( 13 );
    listA->insert_first( 17 );
    listA->insert_first( 19 );
    listA->print_list( "List A" );
    ListNode::print_node_count();
    std::cout << "Deleting List..." << std::endl;
    delete listA;
    ListNode::print_node_count();

    std::cout << std::endl;

    DLList * listB = new DLList();
    listA->insert_first( 23 );
    listA->insert_first( 29 );
    listA->print_list( "List B" );
    ListNode::print_node_count();
    std::cout << "Deleting List..." << std::endl;
    delete listB;
    ListNode::print_node_count();
}

void test9() {
    DLList list;
    list << 5 << 10 << 15 << 20;
    list.print_list();
}

int main( int argc, char ** argv ) {
    if (argc <2) {
	std::cout << "Usage: mytest test1|test2|test3|test4| ..." << std::endl; 
	exit(1);
    }

    std::string test = argv[1];;

    if ( test == "test1" ) {
	test1();
    }
    else if ( test == "test2" ) {
	test2();
    }
    else if ( test == "test3" ) {
	test3();
    }
    else if ( test == "test4" ) {
	test4();
    }
    else if ( test == "test5" ) {
	test5();
    }
    else if ( test == "test6" ) {
	test6();
    }
    else if ( test == "test7" ) {
	test7();
    }
    else if ( test == "test8" ) {
	test8();
    }
    else if ( test == "test9" ) {
	test9();
    }
    else {
	std::cout << "Test Not Found!" << std::endl;
	exit(1);
    }
    return 0;
}
