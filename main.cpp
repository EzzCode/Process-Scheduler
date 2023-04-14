#include <iostream>
#include "Program Classes/Scheduler.h"
using namespace std;

int main() {
	//ui mode
	int mode;
	cout << "please enter operation mode {0, 1, 2}: ";
	cin >> mode;
	while (mode > 2 || mode < 0) {
		cout << "error! enter a valid operation mode: ";
		cin >> mode;
	}
	system("cls");

	//simulate
	Scheduler s = Scheduler(mode);
	s.simulate();

	Process* p1 = new Process(1, 2, 3, 4, 5, 6);
	Process* p2;
	LinkedQueue<Process> prcsQ;
	prcsQ.enqueue(p1);
	bool res = prcsQ.dequeue(p2);
	cout << *p1;
}
