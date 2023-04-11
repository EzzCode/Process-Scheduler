#include <iostream>
#include "Program Classes/Scheduler.h"
using namespace std;

int main() {
	//Scheduler s;
	//s.fileLoading();
	LinkedList<Process> LL;
	LinkedQueue<Process> LQ;
	Process* P1 = new Process(1, 1, 1, 1, 1, 1);
	Process* P2 = new Process(1, 1, 1, 1, 1, 1);
	Process* P3 = new Process(1, 1, 1, 1, 1, 1);
	LL.DeleteFirst();
	LL.InsertEnd(P1);
	LL.InsertEnd(P2);
	LL.InsertBeg(P3);
	LL.DeleteFirst();
	LQ.dequeue(P1);
	LQ.enqueue(P2);
	LQ.enqueue(P3);
	LQ.enqueue(P1);
	LQ.dequeue(P1);

}