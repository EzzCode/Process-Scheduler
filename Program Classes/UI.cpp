#include "UI.h"

UI::UI() {
	set_mode(-1);
}

void UI::set_mode(int val) {
	mode = val;
	//If Silent mode
	if (mode == 2) {
		cout << "Silent Mode...................     Simulation starts..." << endl;
	}
}


void UI::updateTerminal(int tStep, Processor** prcsrList, int prcsrCount, LinkedQueue<Process>& BlkList, LinkedQueue<Process>& TrmList) {
	if (mode == 2) return;	//Silent mode doesn't print
	system("cls");
	int runCount = 0;
	bool firstRun = true;
	//Tstep
	cout << "Current Timestep: " << tStep << endl;
	//RDY
	cout << "---------------------     RDY processes   -----------------------" << endl;
	for (int i = 0; i < prcsrCount; i++) {
		cout << "processor " << i + 1 << " ";
		prcsrList[i]->printRDY();
		cout << endl;

		//To get RUN count
		if (prcsrList[i]->isRunning()) runCount++;
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
		if (prcsrList[i]->isRunning()) {
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

	//Time step end print
	if (mode == 0) {
		cout << "PRESS ANY KEY TO MOVE TO NEXT STEP!" << endl;
		system("pause > nul");
	}
	else {
		this_thread::sleep_for(chrono::seconds(1));
	}
}

void UI::print_end()
{
	system("cls");
	cout << "Simulation ends, Output file created" << endl;
}

UI::~UI() {}