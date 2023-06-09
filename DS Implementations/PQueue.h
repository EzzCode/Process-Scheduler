#pragma once
#include "PNode.h"
#include "QueueADT.h"
using namespace std;

class PQueue:public QueueADT<Process>
{
private:
	PNode<Process>* frontPtr;
	PNode<Process>* backPtr;
	int count;
	void UpdateBack()			//Update the backPtr of the list
	{
		PNode<Process>* P = frontPtr;
		if (P == NULL)
			backPtr = NULL;
		while (P != NULL)
		{
			backPtr = P;
			P = P->GetNext();
		}
	}
public:
	PQueue()				//Constructor
	{
		backPtr = NULL;
		frontPtr = NULL;
		count = 0;
	}

	bool isEmpty() const			//Checks whether Queue is empty or not
	{
		return (frontPtr == NULL);
	}

	bool enqueue(Process* newEntry)			//can't enqueue without specifying priority
	{
		return false;
	}

	bool enqueue(Process* newEntry, int Pri)		//adding a node to the Queue according to its priority
	{
		PNode<Process>* newNodePtr = new PNode<Process>(newEntry);
		newNodePtr->SetPriority(Pri);
		// Insert the new node
		if (isEmpty())	//special case if this is the first node to insert
		{
			frontPtr = newNodePtr; // The queue is empty
			count++;
			UpdateBack();
			return true;
		}
		else
		{
			PNode<Process>* P = frontPtr;
			if (newNodePtr->GetPriority() < frontPtr->GetPriority())
			{
				newNodePtr->SetNext(frontPtr);
				frontPtr = newNodePtr;
				count++;
				UpdateBack();
				return true;
			}
			else
			{
				if (P == NULL)
				{
					backPtr->SetNext(newNodePtr);
					backPtr = newNodePtr; // New node is the last node now
					count++;
					UpdateBack();
					return true;
				}
				while (P->GetNext() != NULL)
				{
						if (newNodePtr->GetPriority() < P->GetNext()->GetPriority())
						{
							newNodePtr->SetNext(P->GetNext());
							P->SetNext(newNodePtr);
							count++;
							UpdateBack();
							return true;
						}
						P = P->GetNext();
				}
				if (P->GetNext() == NULL)
				{
					backPtr->SetNext(newNodePtr);
					backPtr = newNodePtr; // New node is the last node now
					count++;
					UpdateBack();
					return true;
				}
			}
		}
	}

	bool dequeue(Process*& frntEntry)			//Dequeueing like the normal queue because queue is already sorted according to priorities
	{
		if (isEmpty()) return false;

		PNode<Process>* nodeToDeletePtr = frontPtr;
		frntEntry = new Process(*(frontPtr->GetItem()));
		frontPtr = frontPtr->GetNext();
		// Queue is not empty; remove front
		if (nodeToDeletePtr == backPtr)	 // Special case: last node in the queue
			backPtr = NULL;

		// Free memory reserved for the dequeued node
		delete nodeToDeletePtr;
		count--;
		return true;

	}

	bool peek(Process*& frntEntry) const			//copies the first node without dequeueing it
	{
		if (isEmpty())
			return false;

		frntEntry = frontPtr->GetItem();
		return true;

	}

	//getters
	int GetCount()
	{
		return count;
	}

	void printInfo()						//For Printing the Queue
	{
		PNode<Process>* ptr = frontPtr;
		while (ptr) {
			cout << *(ptr->GetItem());
			ptr = ptr->GetNext();
			if (ptr) cout << ", ";
		}
	}

	~PQueue()						//Destructor
	{
		Process* temp;

		//Free (Dequeue) all nodes in the queue
		while (dequeue(temp));
	}

};

