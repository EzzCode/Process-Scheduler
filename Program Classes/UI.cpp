#include "UI.h"

UI::UI() {
	set_mode(-1);
}

void UI::set_mode(int val) {
	mode = val;
}


void UI::updateTerminal(int tStep, Processor** prcsrList, int prcsrCount, LinkedQueue<Process>& BlkList, LinkedQueue<Process>& TrmList) {
	int runCount = 0;
	bool firstRun = true;
	bool isRunning = false;
	//Tstep
	cout << "Current Timestep: " << tStep << endl;
	//RDY
	cout << "---------------------     RDY processes   -----------------------" << endl;
	for (int i = 0; i < prcsrCount; i++) {
		cout << "processor " << i + 1 << " ";
		prcsrList[i]->printRDY();
		cout << endl;

		//To get RUN count
		if (prcsrList[i]->getstate() == 0) runCount++;
	}
	//BLK
	cout << "---------------------     BLK processes   -----------------------" << endl;
	cout << BlkList.GetCount() << " BLK: ";
	BlkList.printInfo();
	cout << endl;
	//RUN
	cout << "---------------------     RUN processes   -----------------------" << endl;
	cout << runCount << " RUN: ";
	for (int i = 0; i < prcsrCount; i++) {
		isRunning = prcsrList[i]->getstate() == 0;
		if (isRunning) {
			if (!firstRun) {
				cout << ", ";
			}
			prcsrList[i]->printRUN();
			cout << "(P" << i + 1 << ")";
			firstRun = false;
		}
	}
	cout << endl;
	//TRM
	cout << "---------------------     TRM processes   -----------------------" << endl;
	cout << TrmList.GetCount() << " TRM: ";
	TrmList.printInfo();
	cout << endl;

	cout << "PRESS ANY KEY TO MOVE TO NEXT STEP!" << endl;
	system("pause > nul");
	system("cls");
}

UI::~UI() {}