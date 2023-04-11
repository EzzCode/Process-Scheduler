#include <iostream>
#include "Program Classes/Scheduler.h"
using namespace std;

int main() {
	Scheduler s;
	s.fileLoading();
	PQueue PQ;
	//LinkedList<Process> LL;
	//LinkedQueue<Process> LQ;
	Process* P1 = new Process(1, 1, 1, 1, 1, 1);
	Process* P2 = new Process(2, 2, 1, 1, 1, 1);
	Process* P3 = new Process(3, 3, 1, 1, 1, 1);
	Process* P4 = new Process(4, 4, 1, 1, 1, 1);
	//LL.DeleteFirst();
	//LL.InsertEnd(P1);
	//LL.InsertEnd(P2);
	//LL.InsertEnd(P3);
	//LL.DeleteNode(3);
	//LL.DeleteFirst();
	//LQ.dequeue(P1);
	//LQ.enqueue(P2);
	//LQ.enqueue(P3);
	//LQ.enqueue(P1);
	//LQ.dequeue(P1);
	PQ.dequeue(P1);
	PQ.enqueue(P1, 5);
	PQ.enqueue(P2, 30);
	PQ.enqueue(P3, 25);
	PQ.enqueue(P4, 4);
	PQ.dequeue(P1);
	PQ.dequeue(P1);
	PQ.dequeue(P1);
	PQ.dequeue(P1);
	PQ.dequeue(P1);

}