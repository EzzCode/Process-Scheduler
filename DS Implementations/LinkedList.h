#pragma once
#include "Node.h"
class LinkedList
{
private:
	Node* Head;
	Node* Tail;
	void UpdateTail()				//Functional
	{
		Node* P = Head;
		while (P != NULL)
		{
			Tail = P;
			P = P->GetNext();
		}
		if (P == NULL)
			Tail = NULL;
	}
public:
	LinkedList()
	{
		Head = NULL;
		Tail = NULL;
	}
	~LinkedList()
	{
		DeleteAll();
	}


	void InsertBeg(Process* data)			//Functional
	{
		Node* R = new Node;
		R->SetItem(data);
		R->SetNext(Head);
		Head = R;
		UpdateTail();
	}

	void DeleteAll()				//Functional
	{
		Node* P = Head;
		while (Head)
		{
			P = Head->GetNext();
			delete Head;
			Head = P;
		}
	}

	void PrintList()			//Functional
	{
		Node* P = Head;

		while (P != NULL)
		{
			cout << "[" << P->GetItem() << "]" << "-->";
			P = P->GetNext();
		}
		cout << "NULL" << endl;
	}

	void InsertEnd(Process* data)		//Functional
	{
		Node* P = new Node;
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
	}

	bool Find(Process* data)			//Functional
	{
		if (Head != NULL)
		{
			Node* P = Head;
			while (P != NULL)
			{
				if (P->GetItem() == data)
					return true;
				P = P->GetNext();
			}
		}
		return false;
	}

	int CountOccurance(Process* data)		//Functional
	{
		int count = 0;
		if (Head != NULL)
		{
			Node* P = Head;
			while (P != NULL)
			{
				if (P->GetItem() == data)
					count++;
				P = P->GetNext();
			}
		}
		return count;
	}

	void DeleteFirst()			//Functional
	{
		if (Head != NULL)
		{
			Node* P = Head->GetNext();
			delete Head;
			Head = P;
		}
	}

	void DeleteLast()			//Functional
	{
		if (Tail != NULL)
		{
			Node* P = Head;
			while (P->GetNext() != Tail)
			{
				P = P->GetNext();
			}
			P->SetNext(NULL);
			delete Tail;
			Tail = P;
		}
	}

	bool DeleteNode(Process* data)				//Functional
	{
		Node* P = Head;
		if (P != NULL)
		{
			if (P->GetItem() == data)
			{
				Head = P->GetNext();
				delete P;
				return true;
			}
			while (P->GetNext() != NULL)
			{
				if (P->GetNext()->GetItem() == data)
				{
					Node* R = P->GetNext()->GetNext();
					delete P->GetNext();
					P->SetNext(R);
					return true;
					UpdateTail();
				}
				P = P->GetNext();
			}
		}
		UpdateTail();
		return false;
	}

	bool DeleteNodes(Process* data)				//Functional
	{
		bool b = false;
		Node* P = Head;
		if (P != NULL)
		{
			if (P->GetItem() == data)
			{
				Head = P->GetNext();
				delete P;
				b = true;
			}
			P = Head;
			while (P->GetNext() != NULL)
			{
				if (P->GetNext()->GetItem() == data)
				{
					Node* R = P->GetNext()->GetNext();
					delete P->GetNext();
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

	Process* GetHeadData()
	{
		if (Head != NULL)
		{
			Process* P1 = new Process(*(Head->GetItem()));
			Node* R = Head;
			Head = Head->GetNext();
			delete R;
			R = NULL;
			UpdateTail();
			return P1;
		}
	}

};

