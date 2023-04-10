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
#include "Node.h"
#include "QueueADT.h"
#include <vector>
using namespace std;


class LinkedQueue :public QueueADT
{
private:

	Node* backPtr;
	Node* frontPtr;
public:
	LinkedQueue();
	bool isEmpty() const;
	bool enqueue(Process* newEntry);
	bool dequeue(Process*& frntEntry);
	bool peek(Process*& frntEntry)  const;
	~LinkedQueue();

	//copy constructor
	LinkedQueue(const LinkedQueue& LQ);
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/


LinkedQueue::LinkedQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
bool LinkedQueue::isEmpty() const
{
	return (frontPtr == nullptr);
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

bool LinkedQueue::enqueue(Process* newEntry)
{
	Node* newNodePtr = new Node(newEntry);
	// Insert the new node
	if (isEmpty())	//special case if this is the first node to insert
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->SetNext(newNodePtr); // The queue was not empty

	backPtr = newNodePtr; // New node is the last node now
	return true;
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

bool LinkedQueue::dequeue(Process*& frntEntry)
{
	if (isEmpty())
		return false;

	Node* nodeToDeletePtr = frontPtr;
	//frntEntry->set_AT(frontPtr->GetItem()->get_AT());
	//frntEntry->set_PID(frontPtr->GetItem()->get_PID());
	//frntEntry->set_CT(frontPtr->GetItem()->get_CT());
	//frntEntry->set_RT(frontPtr->GetItem()->get_RT());
	//frntEntry->set_TT(frontPtr->GetItem()->get_TT());
	//frntEntry->set_state(frontPtr->GetItem()->get_state());
	//frntEntry->set_IO_R(frontPtr->GetItem()->get_IO_R());
	//frntEntry->set_IO_D(frontPtr->GetItem()->get_IO_D());
	//frntEntry->set_SIGKILL(frontPtr->GetItem()->get_SIGKILL());

	frntEntry = new Process(*(frontPtr->GetItem()));


	frontPtr = frontPtr->GetNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
		backPtr = NULL;

	// Free memory reserved for the dequeued node
	delete nodeToDeletePtr;

	return true;

}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: peek
copies the front of this queue to the passed param. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
*/

bool LinkedQueue::peek(Process*& frntEntry) const
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
LinkedQueue::~LinkedQueue()
{
	//Free (Dequeue) all nodes in the queue
	while (!isEmpty())
	{
		Process* ptr;
		dequeue(ptr);
		frontPtr = frontPtr->GetNext();
	}
	frontPtr = NULL;
	backPtr = NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////
/*
Function: Copy constructor
To avoid shallow copy,
copy constructor is provided

Input: LinkedQueue<T>: The Queue to be copied
Output: none
*/

LinkedQueue::LinkedQueue(const LinkedQueue& LQ)
{
	Node* NodePtr = LQ.frontPtr;
	if (!NodePtr) //LQ is empty
	{
		frontPtr = backPtr = nullptr;
		return;
	}

	//insert the first node
	Node* ptr = new Node(NodePtr->GetItem());
	frontPtr = backPtr = ptr;
	NodePtr = NodePtr->GetNext();

	//insert remaining nodes
	while (NodePtr)
	{
		Node* ptr = new Node(NodePtr->GetItem());
		backPtr->SetNext(ptr);
		backPtr = ptr;
		NodePtr = NodePtr->GetNext();
	}
}

#endif