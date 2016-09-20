#include "DLList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

DLList::DLList()
{
	head = new DLNode();
	head->next = head;
	head->prev = head;
}

DLList::~DLList()
{
	head->next = head;
	head->prev = head;
	
}

//ADD SORT FUNCTION
void DLList::sort(int ascending)
{
	DLNode * e = head->next;
	e->prev = head;
	e->next->prev = e;
	e->prev->next = e;
	DLNode * e1 = e;
	if(ascending == 1){
		while(e != head){
			while(e1 != head){			
				if(e1->data < e->data){
					int temp = e1->data;
					e1->data = e->data;
					e->data = temp;
				}
				e1 = e1->next;
			}
			e = e->next;
			e1 = e;
		}
	}else if(ascending == 0){
		while(e != head){
			while(e1 != head){			
				if(e1->data > e->data){
					int temp = e1->data;
					e1->data = e->data;
					e->data = temp;
				}
				e1 = e1->next;
			}
			e = e->next;
			e1 = e;
		}
	}
}
//

void DLList::print()
{
	DLNode * e = head->next;
	e->prev = head;
	e->next->prev = e;
	e->prev->next = e;
	
	while(e != head){
		printf("%d\n",e->data);
		e = e->next;
	}
}

void DLList::printSorted()
{
	DLNode * e = head->next;
	e->prev = head;
	e->next->prev = e;
	e->prev->next = e;
	DLNode * e1 = e;
	int * store = (int*)malloc(sizeof(int)*1000);
	int * store2 = store;
	//save original DLList->data
	while(e != head){
		*store2 = e->data;
		store2++;
		e = e->next;
	}

	//SORT DLList
/*	e = head->next;
	while(e != head){
		while(e1 != head){
			if(e1->data < e->data){
				int temp = e1->data;
				e1->data = e->data;
				e->data = temp;
			}
			e1 = e1->next;
		}
		e = e->next;
		e1 = e;
	}
*/
	DLList::sort(1);
	DLList::print();

	//resume to original DLList
	e = head->next;
	while(e != head){
		e->data = *store;
		e = e->next;
		store++;
	}

}

void DLList::insertFront(int data)
{
	DLNode * e = new DLNode();
	e->data = data;
	e->next = head->next;
	e->prev = head;
	e->next->prev = e;
	e->prev->next = e;
}

//ADD insertLast
void DLList::insertLast(int data)
{
	DLNode * e = new DLNode();
	e->data = data;
	DLNode * p = head->next;
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
//

bool DLList::removeLast(int & data)
{
	DLNode * e = head->next;
	e->prev = head;
	e->prev->next = e;
	e->next->prev = e;
	if(e == head){
		return false;
	}
	while(e->next != head){
		e = e->next;
	}
	data = e->data;
	e->prev->next = head;
	e->next->prev = e->prev;

	delete e;
	return true;
}

DLList * DLList::difference(DLList & list)
{
	DLList * diff = new DLList();
	DLNode * e = head->next;
	e->prev = head;
	e->prev->next = e;
	e->next->prev = e;

	DLNode * i = list.head->next;
	i->prev = list.head;
	i->prev->next = i;
	i->next->prev = i;
	
	int flag = 0;
	while(e != head){
		while(i != list.head){
			if(e->data == i->data){
				flag = 1;
				break;
			}
			i = i->next;
		}
		if(flag == 0){
			diff->insertLast(e->data);
		}
		flag = 0;
		e = e->next;
		i = list.head->next;
	}
//	diff->sort(0);
	return diff;
}

DLList * DLList::getRange(int start, int end)
{
	DLList * range = new DLList();
	DLNode * e = head->next;
	e->prev = head;
	e->prev->next = e;
	e->next->prev = e;
	while(e != head){
		if(e->data > start && e->data < end){
			range->insertFront(e->data);
		}
		e = e->next;
	}
	return range;
}

DLList * DLList::intersection(DLList & list)
{
	DLList * inter = new DLList();
	DLNode * e = head->next;
	e->prev = head;
	e->prev->next = e;
	e->next->prev = e;
	DLNode * i = list.head->next;
	i->prev = list.head;
	i->prev->next = i;
	i->next->prev = i;
	while(e != head){
		while(i != list.head){
			if(e->data == i->data){
				inter->insertFront(e->data);
			}
			i = i->next;
		}
		e = e->next;
		i = list.head->next;
	}
	inter->sort(0);
	return  inter;
}

void DLList::removeRange(int start, int end)
{
	DLNode * e = head->next;
	e->prev = head;
	e->prev->next = e;
	e->next->prev = e;
	DLNode * p = e;
	while(e != head){
		if(e->data > start && e->data< end){
			p = e->prev;
			p->next = e->next;
			e->next->prev = p;
			e = p;
		}
		e = e->next;
	}
}
