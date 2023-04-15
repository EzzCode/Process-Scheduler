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
		Pri = 0;
		Item = newItem;
		Next = NULL;
	}

	~PNode()
	{
		delete Item;
		Item = NULL;
	}

	//Copy constructor
	PNode(const PNode& other) {
		Item = new T(*(other.Item));
		Pri = other.Pri;
		Next = nullptr;
	}
	//Overload assignment op.
	PNode& operator=(const PNode& other) {
		if (this != &other) {
			Item = new T(*(other.Item));
			Pri = other.Pri;
			Next = nullptr;
		}
		return *this;
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

