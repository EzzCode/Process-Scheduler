#pragma once
#include "PNode.h"
#include "../Program Classes/Process.h"
template < typename T>
class LinkedList
{
private:
	PNode<T>* Head;
	PNode<T>* Tail;
	int count;
	void UpdateTail()				//Update the Tail of the list
	{
		PNode<T>* P = Head;
		if (P == NULL)
			Tail = NULL;
		while (P != NULL)
		{
			Tail = P;
			P = P->GetNext();
		}
	}
public:
	LinkedList()					//Default Constructor
	{
		Head = NULL;
		Tail = NULL;
		count = 0;
	}
	~LinkedList()					//Destructor
	{
		DeleteAll();
	}

	int GetCount()					//Getter for count of Nodes in the List
	{
		return count;
	}

	void InsertBeg(T* data)			//Insert given data in a node at the Head of the LinkedList
	{
		PNode<T>* R = new PNode<T>;
		R->SetItem(data);
		R->SetNext(Head);
		Head = R;
		UpdateTail();
		count++;
	}

	void DeleteAll()				//Delete All Nodes
	{
		PNode<T>* P = Head;
		while (Head)
		{
			P = Head->GetNext();
			delete Head;
			Head = P;
		}
		count = 0;
	}

	void InsertEnd(T* data)		//Insert given data in a node at the Tail of the LinkedList
	{
		PNode<T>* P = new PNode<T>;
		P->SetItem(data);
		if (Head != NULL)
		{
			Tail->SetNext(P);
			Tail = P;
		}
		else
		{
			Head = P;
			Tail = P;
		}
		count++;
	}

	bool Find(T* data)			//Checks whether the LinkedList contains a node with the given data or not
	{
		if (Head != NULL)
		{
			PNode<Process>* P = Head;
			while (P != NULL)
			{
				if (P->GetItem()->get_PID() == data)
					return true;
				P = P->GetNext();
			}
		}
		return false;
	}


	void DeleteFirst()			//Delete first node
	{
		if (Head != NULL)
		{
			PNode<T>* P = Head->GetNext();
			delete Head;
			count--;
			Head = P;
		}
	}

	void DeleteLast()			//Delete last node
	{
		if (Tail != NULL)
		{
			PNode<T>* P = Head;
			while (P->GetNext() != Tail)
			{
				P = P->GetNext();
			}
			P->SetNext(NULL);
			delete Tail;
			count--;
			Tail = P;
		}
	}



	bool DeleteNode(T* data)				//Delete the first node that match the given data
	{
		PNode<T>* P = Head;
		if (P != NULL)
		{
			if (P->GetItem() == data)
			{
				Head = P->GetNext();
				delete P;
				count--;
				return true;
			}
			while (P->GetNext() != NULL)
			{
				if (P->GetNext()->GetItem() == data)
				{
					PNode<T>* R = P->GetNext()->GetNext();
					delete P->GetNext();
					P->SetNext(R);
					count--;
					UpdateTail();
					return true;
				}
				P = P->GetNext();
			}
		}
		UpdateTail();
		return false;
	}

	bool DeleteNode(int pID)		//Only works for Processes
	{
		PNode<Process>* P = Head;
		if (P != NULL)
		{
			if (P->GetItem()->get_PID() == pID)
			{
				Head = P->GetNext();
				delete P;
				count--;
				return true;
			}
			while (P->GetNext() != NULL)
			{
				if (P->GetNext()->GetItem()->get_PID() == pID)
				{
					PNode<Process>* R = P->GetNext()->GetNext();
					delete P->GetNext();
					count--;
					P->SetNext(R);
					UpdateTail();
					return true;
				}
				P = P->GetNext();
			}
		}
		UpdateTail();
		return false;
	}

	bool DeleteNodes(T* data)		//Delete all nodes that match the given data
	{
		bool b = false;
		PNode<T>* P = Head;
		if (P != NULL)
		{
			if (P->GetItem() == data)
			{
				Head = P->GetNext();
				delete P;
				count--;
				b = true;
			}
			P = Head;
			while (P->GetNext() != NULL)
			{
				if (P->GetNext()->GetItem() == data)
				{
					PNode<T>* R = P->GetNext()->GetNext();
					delete P->GetNext();
					count--;
					P->SetNext(R);
					b = true;
					UpdateTail();
				}
				P = P->GetNext();
			}
		}
		UpdateTail();
		return b;
	}

	bool DeleteNodes(int pID)			//Only works for Processes
	{
		bool b = false;
		PNode<Process>* P = Head;
		if (P != NULL)
		{
			if (P->GetItem()->get_PID() == pID)
			{
				Head = P->GetNext();
				delete P;
				count--;
				b = true;
			}
			P = Head;
			while (P->GetNext() != NULL)
			{
				if (P->GetNext()->GetItem()->get_PID() == pID)
				{
					PNode<Process>* R = P->GetNext()->GetNext();
					delete P->GetNext();
					count--;
					P->SetNext(R);
					b = true;
					UpdateTail();
				}
				P = P->GetNext();
			}
		}
		UpdateTail();
		return b;
	}

	T* GetHeadData()			//To Dequeue the first Item of the First Node
	{
		if (Head != NULL)
		{
			T* P1 = new T(*(Head->GetItem()));
			PNode<T>* R = Head;
			Head = Head->GetNext();
			delete R;
			R = NULL;
			UpdateTail();
			count--;
			return P1;
		}
		return NULL;
	}

	bool kill_prcs(int pID, bool killOrph, Process*& p)		// For SIGKILL and killing orphans
	{
		// when sigkill is intended: pID is set to ID of prcs to be killed
		// and killOrph is set to false
		// when killing orphans is intended: pID is set to a -ve number
		// so any checks on it will never be true as all IDs are +ve
		// and killOrph is set to true
		PNode<Process>* ptr = Head;
		if (ptr != NULL)
		{
			// check for 2 cond:
			// 1- sigkill is performed
			// 2- killOrph is performed
			if (ptr->GetItem()->get_PID() == pID || (killOrph && ptr->GetItem()->get_state() == 5))
			{
				PNode<Process>* temp = Head;
				Head = ptr->GetNext();
				p = new Process(*(ptr->GetItem()));
				delete temp;
				temp = nullptr;
				count--;
				UpdateTail();
				return true;
			}
			while (ptr->GetNext() != NULL)
			{
				if (ptr->GetNext()->GetItem()->get_PID() == pID || (killOrph && ptr->GetItem()->get_state() == 5))
				{
					PNode<Process>* temp = ptr->GetNext();
					PNode<Process>* R = ptr->GetNext()->GetNext();
					p = new Process(*(ptr->GetNext()->GetItem()));
					ptr->SetNext(R);
					delete temp;
					temp = nullptr;
					count--;
					UpdateTail();
					return true;
				}
				ptr = ptr->GetNext();
			}
		}
		UpdateTail();
		return false;
	}

	void printInfo()		//For Printing the Linked List
	{
		PNode<T>* ptr = Head;
		while (ptr) {
			cout << *(ptr->GetItem());
			ptr = ptr->GetNext();
			if (ptr) cout << ", ";
		}
	}

};

