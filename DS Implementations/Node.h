#ifndef _NODE
#define _NODE
#include "../Program Classes/Process.h"
//First let's declare a single node in the list
class Node
{
private :
	Process* item;	// A data item (can be any complex sturcture)
	Node* next;	// Pointer to next node
public :

	Node( ) //default constructor
	{
		next= nullptr;
	} 

	Node(Process* newItem) //non-default constructor
	{
		item = newItem;
		next= nullptr;

	}

	Node(const Process* r_Item, Node* nextNodePtr)
	{
		item = r_Item;
		next = nextNodePtr;
	}

	void setItem(Process newItem)
	{
		item = newItem;
	} // end setItem

	void setNext(Node* nextNodePtr)
	{
	next = nextNodePtr;
	} // end setNext

	Process getItem() const
	{
		return item;
	} // end getItem

	Node* getNext() const
	{
		return next;
	}
}; // end Node

#endif	
