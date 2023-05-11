#include <iostream>
#include "Program Classes/Scheduler.h"
using namespace std;

int main() {
	//UI mode
	int mode;
	cout << "Please enter operation mode {0, 1, 2}: ";
	cin >> mode;
	while (mode > 2 || mode < 0) {
		cout << "Error! enter a valid operation mode: ";
		cin >> mode;
	}
	system("cls");

	//Simulate
	Scheduler s = Scheduler(mode);
	s.simulate();
}
