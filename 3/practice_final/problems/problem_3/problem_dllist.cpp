#include <iostream>
#include <string>
#include "DLList.h"

// Constructor
// DO NOT CHANGE
DLList::DLList() 
{
    head = new ListNode();
    head->next = head;
    head->prev = head;
}

// Prints the list
// DO NOT CHANGE
void DLList::print_list() 
{
    std::cout << "Printing List..." << std::endl;
    if ( head->next == head ) {
	std::cout << "Empty List" << std::endl;
    }
    else {
	ListNode * e = head->next;  
	while ( e != head) {
	    if ( e->next != head )
		std::cout << e->value << ", ";
	    else 
		std::cout << e->value;
	    e = e->next;
	}
	std::cout << std::endl;
    }
}

// Prints the list given a list name
// DO NOT CHANGE
void DLList::print_list( std::string list_name ) 
{
    std::cout << "Printing " << list_name << "..." << std::endl;
    if ( head->next == head ) {
	std::cout << "Empty List" << std::endl;
    }
    else {
	ListNode * e = head->next;  
	while ( e != head) {
	    if ( e->next != head )
		std::cout << e->value << ", ";
	    else 
		std::cout << e->value;
	    e = e->next;
	}
	std::cout << std::endl;
    }
}

// Problem (1/5)
/******************************************************************************
 * TODO: Write the destructor. The destructor should delete all of the 
 * list nodes from the list. 
 *****************************************************************************/
DLList::~DLList()
{
    // Write Your Code Here
	ListNode * e = head->next;
	e->prev = head;
	e->next->prev = e;
	e->prev->next = e;
	ListNode * p = e;
	
	while(e != head){
		p = e->prev;
		p->next = e->next;
		e->next->prev = p;
		e = p;
		ListNode::node_count -- ;
		e = e->next;
	}
	ListNode::node_count--;

}

// Problem (2/5)
/******************************************************************************
 * TODO: Insert a new ListNode to the beginning of the double linked list. 
 * Remember the list head is a sentinel node, do not change head. 
 * Set the value of the new node to the parameter 'value'.
 * 
 * Parameters: value -- set the value of the node equal to this
 *
 * Return: void 
 *
 * Return Type: void
 *****************************************************************************/
void DLList::insert_first( int value ) 
{
    // Write Your Code Here
    ListNode *e = new ListNode();
    e->value = value;
    e->next = head->next;
    e->prev = head;
    e->next->prev = e;
    e->prev->next = e;

}


// Problem (3/5)
/******************************************************************************
 * TODO: Remove the node from the double linked list whose value equals the 
 * parameter 'value', return true after deleting the node. If the node does not
 * exist in the list or the list is empty, return false;
 * 
 * Parameters: value -- remove the node whose value is equal to this
 *
 * Return: true if the node was removed successfully
 *         false if the value does not exist in the list or the list is empty
 *
 * Return Type: void
 *****************************************************************************/
bool DLList::remove( int value ) 
{
    // Write Your Code Here
    ListNode * e = head->next;
    e->prev = head;
    e->prev->next = e;
    e->next->prev = e;
    ListNode * p = e;
    while(e != head){
    	if(e->value == value){
		p = e->prev; 
		p->next = e->next;
		e->next->prev = p;
		free(e);
		return true;
	}
	e = e->next;
    }
    return false;
}

// Problem (4/5)
/*****************************************************************************
* TODO: Add the values of listB to the end of the list. 
* 
* Parameters: listB -- add the values of 'listB' to the end of list
*
* e.g. ListA = 3, 1, 4
*      ListB = 6, 2
*      ListA.concat_list(&listB) should change ListA to 3, 1, 4, 6, 2
*
*      ListB should not be changed.
*
* Return: void
*
* Return Type: void
*****************************************************************************/
void DLList::insert_last(int value){
	ListNode * e = new ListNode();
	e->value = value;
	ListNode * p = head->next;
	p->prev = head;
	p->prev->next = p;
	p->next->prev = p;
	while(p->next != head){
		p = p->next;
	}
	p->next = e;
	e->next = head;
	head->prev = e;
	e->prev = p;

}

void DLList::concat_list( DLList * listB ) 
{
    // Write Your Code Here
    int * save;
    int count = 0;
    save = (int*)malloc(sizeof(int)* 100);
    int *save1 = save;
    ListNode * b1 = listB->head->next;
    while(b1 != listB->head){
    	*save1 = b1->value;
	b1 = b1->next;
	save1++;
	count++;
    }
    /*
    int j = 0;
    int * test = save;
    for(j;j<count;j++){
    	printf("%d\n",*test);
	test++;
    }
    */
    int i = 0;
    for(i;i<count;i++){
    	insert_last(*save);
	save++;
    }
    
}

// Problem (5/5)
/*****************************************************************************
* TODO: Overload the operator '<<' for insert_first. 
*****************************************************************************/
DLList & DLList::operator << (const int value ) 
{
    // Write Your Code Here
	this->insert_first(value);
	return *this;
}
