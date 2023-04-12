#include "UI.h"
UI::UI() {
	tStep = 0;
	runCount = 0;
	prcsrCount = 0;
	set_mode(-1);
	isRunning = false;
	prcsrList = nullptr;
}

void UI::set_mode(int val) {
	mode = val;
}


void UI::updateTerminal(int timestep, Processor** processorList, int processorCount, LinkedQueue<Process>& Blk, LinkedQueue<Process>& Trm) {
	tStep = timestep;
	prcsrList = processorList;
	prcsrCount = processorCount;
	BlkList = Blk;
	TrmList = Trm;
	runCount = 0;
	PrintScreen();
}

void UI::PrintScreen() {
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
	bool firstRun = true;
	for (int i = 0; i < prcsrCount; i++) {
		isRunning = prcsrList[i]->getstate() == 0;
		if (isRunning) {
			if (!firstRun) {
				cout << ", ";
			}
			cout << (prcsrList[i]) << "(P" << i + 1 << ")";
			firstRun = false;
		}
	}
	//cout << "\b\b";
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