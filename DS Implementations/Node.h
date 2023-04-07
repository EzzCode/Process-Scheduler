#ifndef _NODE
#define _NODE

//First let's declare a single node in the list
template<typename T>
class Node
{
private :
	T item;	// A data item (can be any complex sturcture)
	Node<T>* next;	// Pointer to next node
public :

	Node( ) //default constructor
	{
		next= nullptr;
	} 

	Node( T newItem) //non-default constructor
	{
		item = newItem;
		next= nullptr;

	}

	Node(const T& r_Item, Node<T>* nextNodePtr)
	{
		item = r_Item;
		next = nextNodePtr;
	}

	void setItem( T newItem)
	{
		item = newItem;
	} // end setItem

	void setNext(Node<T>* nextNodePtr)
	{
	next = nextNodePtr;
	} // end setNext

	T getItem() const
	{
		return item;
	} // end getItem

	Node<T>* getNext() const
	{
		return next;
	}
}; // end Node

#endif	
