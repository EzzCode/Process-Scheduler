#pragma once
#include <iostream>
using namespace std;
template < typename T>
class PNode
{
private:
	T* Item;
	PNode<T>* Next;
	int Pri;		//Priority
public:

	//Constructors->Destructor
	PNode()			// default constructor
	{
		Pri = 0;
		Item = NULL;
		Next = NULL;
	}

	PNode(T* newItem) //non-default constructor
	{
		Item = newItem;
		Next = NULL;
	}

	~PNode()
	{
		Item = NULL;
		delete Item;
		Next = NULL;
		delete Next;
	}

	//Getters
	T* GetItem() const
	{
		return Item;
	}

	PNode<T>* GetNext()
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
	void SetNext(PNode<T>* next)
	{
		Next = next;
	}
	void SetPriority(int data)
	{
		Pri = data;
	}
};

