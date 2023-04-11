/*

				The Node: item of type T and a "next" pointer
					-------------
					| item| next | --->
					-------------
General Queue case:

				 frontPtr																backPtr
					\											   						/
					 \											  					   /
					------------- 	  ------------- 	  ------------- 	  -------------
					| item| next |--->| item| next |--->  | item| next |--->  | item| next |---> NULL
					------------- 	  ------------- 	  ------------- 	  -------------

Empty Case:

				 frontptr	 backptr
						\	 /
						 \	/
					---- NULL ------


Single Node Case:
				 frontPtr	 backPtr
					\		/
					 \	   /
					-----------
					|item| next| -->NULL
					-----------

*/

#ifndef LINKED_QUEUE_
#define LINKED_QUEUE_
#pragma once
#include "PNode.h"
#include "QueueADT.h"
using namespace std;

template <typename T>
class LinkedQueue :public QueueADT<T>
{
private:

	PNode<T>* backPtr;
	PNode<T>* frontPtr;
	int count;
public:
	/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/


	LinkedQueue()
	{
		backPtr = nullptr;
		frontPtr = nullptr;
		count = 0;
	}
	/////////////////////////////////////////////////////////////////////////////////////////

	/*
	Function: isEmpty
	Sees whether this queue is empty.

	Input: None.
	Output: True if the queue is empty; otherwise false.
	*/
	bool isEmpty() const
	{
		return (frontPtr == nullptr);
	}

	/////////////////////////////////////////////////////////////////////////////////////////

	/*Function:enqueue
	Adds newEntry at the back of this queue.

	Input: newEntry .
	Output: True if the operation is successful; otherwise false.
	*/

	bool enqueue(T*& newEntry)
	{
		PNode<T>* newNodePtr = new PNode<T>(newEntry);
		// Insert the new node
		if (isEmpty())	//special case if this is the first node to insert
			frontPtr = newNodePtr; // The queue is empty
		else
			backPtr->SetNext(newNodePtr); // The queue was not empty

		backPtr = newNodePtr; // New node is the last node now
		count++;
		return true;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Output: True if the operation is successful; otherwise false.
*/

	bool dequeue(T*& frntEntry)
	{
		if (isEmpty())
			return false;

		PNode<T>* nodeToDeletePtr = frontPtr;
		frntEntry = frontPtr->GetItem();
		frontPtr = frontPtr->GetNext();
		// Queue is not empty; remove front
		if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
			backPtr = nullptr;

		// Free memory reserved for the dequeued node
		delete nodeToDeletePtr;
		count--;
		return true;

	}

	/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/

	bool peek(T*& frntEntry) const
	{
		if (isEmpty())
			return false;

		frntEntry = frontPtr->GetItem();
		return true;

	}

	///////////////////////////////////////////////////////////////////////////////////
/*
Function: destructor
removes all nodes from the queue by dequeuing them
*/
	~LinkedQueue()
	{
		T* temp;

		//Free (Dequeue) all nodes in the queue
		while (dequeue(temp));
	}

	/////////////////////////////////////////////////////////////////////////////////////////
	/*
	Function: Copy constructor
To avoid shallow copy,
copy constructor is provided

Input: LinkedQueue<T>: The Queue to be copied
Output: none
*/

	LinkedQueue(const LinkedQueue& LQ)
	{
		PNode<T>* NodePtr = LQ.frontPtr;
		if (!NodePtr) //LQ is empty
		{
			frontPtr = backPtr = nullptr;
			return;
		}

		//insert the first node
		PNode<T>* ptr = new PNode<T>(NodePtr->GetItem());
		frontPtr = backPtr = ptr;
		NodePtr = NodePtr->GetNext();

		//insert remaining nodes
		while (NodePtr)
		{
			PNode<T>* ptr = new PNode<T>(NodePtr->GetItem());
			backPtr->SetNext(ptr);
			backPtr = ptr;
			NodePtr = NodePtr->GetNext();
		}
	}
};

#endif