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
	void UpdateTail()				//Functional
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
	LinkedList()
	{
		Head = NULL;
		Tail = NULL;
		count = 0;
	}
	~LinkedList()
	{
		DeleteAll();
	}

	int GetCount()
	{
		return count;
	}

	void InsertBeg(T* data)			//Functional
	{
		PNode<T>* R = new PNode<T>;
		R->SetItem(data);
		R->SetNext(Head);
		Head = R;
		UpdateTail();
		count++;
	}

	void DeleteAll()				//Functional
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

	void PrintList()			//Functional
	{
		PNode<T>* P = Head;

		while (P != NULL)
		{
			cout << "[" << P->GetItem() << "]" << "-->";
			P = P->GetNext();
		}
		cout << "NULL" << endl;
	}

	void InsertEnd(T* data)		//Functional
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

	bool Find(T* data)			//Functional
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


	void DeleteFirst()			//Functional
	{
		if (Head != NULL)
		{
			PNode<T>* P = Head->GetNext();
			delete Head;
			count--;
			Head = P;
		}
	}

	void DeleteLast()			//Functional
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

	bool DeleteNode(int data)		//Only works for Processes
	{
		PNode<Process>* P = Head;
		if (P != NULL)
		{
			if (P->GetItem()->get_PID() == data)
			{
				Head = P->GetNext();
				delete P;
				count--;
				return true;
			}
			while (P->GetNext() != NULL)
			{
				if (P->GetNext()->GetItem()->get_PID() == data)
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

	bool DeleteNode(T* data)				//Functional
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

	bool DeleteNodes(int data)			//Only works for Processes
	{
		bool b = false;
		PNode<Process>* P = Head;
		if (P != NULL)
		{
			if (P->GetItem()->get_PID() == data)
			{
				Head = P->GetNext();
				delete P;
				count--;
				b = true;
			}
			P = Head;
			while (P->GetNext() != NULL)
			{
				if (P->GetNext()->GetItem()->get_PID() == data)
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

	bool DeleteNodes(T* data)		//Functional
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

	T* GetHeadData()
	{
		if (Head != NULL)
		{
			T* P1 = new T(*(Head->GetItem()));
			PNode<T>* R = Head;
			Head = Head->GetNext();
			delete R;
			R = NULL;
			UpdateTail();
			return P1;
		}
		return NULL;
	}
};

