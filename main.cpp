#include <iostream>
#include "Program Classes/Scheduler.h"
using namespace std;

int main() {
	//UI mode
	int mode;
	cout << "Please Enter operation mode {0, 1, 2}: ";
	cin >> mode;
	while (mode > 2 || mode < 0) {
		cout << "Error! Enter a valid operation mode: ";
		cin >> mode;
	}

	//Simulate
	Scheduler s;
	s.fileLoading();
}
