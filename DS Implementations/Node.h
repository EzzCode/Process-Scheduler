#ifndef _NODE
#define _NODE
#include "../Program Classes/Process.h"
#pragma once
#include <iostream>
using namespace std;
class Node
{
private:
	Process* Item;
	Node* Next;
public:
	Node()			// default constructor
	{
		Item = NULL;
		Next = NULL;
	}

	Node(Process* newItem) //non-default constructor
	{
		Item = newItem;
		Next = NULL;
	}

	Node(Process* item, Node* nextNodePtr)
	{
		Item = item;
		Next = nextNodePtr;
	}

	~Node()
	{
		delete Item;
		Item = NULL;
		delete Next;
		Next = NULL;
	}

	Process* GetItem() const
	{
		return Item;
	}
	Node* GetNext()
	{
		return Next;
	}

	void SetItem(Process* item)
	{
		Item = item;
	}
	void SetNext(Node* next)
	{
		Next = next;
	}
};

#endif