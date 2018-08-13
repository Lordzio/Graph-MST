#include "stdafx.h"
#include "myList.h"


myList::myList()
{
	head = new(std::nothrow)Element;
	head->next = NULL;
	head->data = "NULL";
	length = 1;
}


myList::~myList()
{
	delete head;
}

void myList::insert(std::string dat) {
	if (head->data.compare("NULL")) {
		head->data = dat;
	}
	else {

		Element *e = new(std::nothrow)Element;

		e->data = dat;
		e->next = head;
		head = e;
	}

}
