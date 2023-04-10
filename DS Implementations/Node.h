#ifndef _NODE
#define _NODE
#pragma once
#include <iostream>
using namespace std;
template < typename T>
class Node
{
private:
	T* Item;
	Node<T>* Next;
public:
	Node()			// default constructor
	{
		Item = NULL;
		Next = NULL;
	}

	Node(T* newItem) //non-default constructor
	{
		Item = newItem;
		Next = NULL;
	}

	Node(T* item, Node<T>* nextNodePtr)
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

	T* GetItem() const
	{
		return Item;
	}
	Node<T>* GetNext()
	{
		return Next;
	}

	void SetItem(T* item)
	{
		Item = item;
	}
	void SetNext(T* next)
	{
		Next = next;
	}
};

#endif