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
}
