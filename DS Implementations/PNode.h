#pragma once
#include <iostream>
using namespace std;
template < typename T>
class PNode
{
private:
	T* Item;
	Node<T>* Next;
	int Pri;		//Priority
public:

	//Constructors->Destructor
	PNode()			// default constructor
	{
		Priority = 0;
		Item = NULL;
		Next = NULL;
	}

	PNode(T* newItem) //non-default constructor
	{
		Item = newItem;
		Next = NULL;
	}

	PNode(T* item, Node<T>* nextNodePtr)
	{
		Item = item;
		Next = nextNodePtr;
	}

	~PNode()
	{
		Item = NULL;
		delete Item;
	}

	//Getters
	T* GetItem() const
	{
		return Item;
	}

	Node<T>* GetNext()
	{
		return Next;
	}

	int GetPriority()
	{
		return Pri;
	}

	//Setters
	void SetItem(T* item)
	{
		Item = item;
	}
	void SetNext(T* next)
	{
		Next = next;
	}
	void SetPriority(int data)
	{
		Pri = data;
	}
};

