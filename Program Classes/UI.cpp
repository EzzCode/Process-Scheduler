#include "UI.h"
UI::UI() {
	tStep = 0;
	runCount = 0;
	prcsrCount = 0;
	mode = -1;
	isRunning = false;
	prcsrList = nullptr;
}

void UI::updateTerminal(int timestep, Processor** processorList, int processorCount, LinkedQueue<Process>& Blk, LinkedQueue<Process>& Trm, int mode) {
	tStep = timestep;
	prcsrList = processorList;
	prcsrCount = processorCount;
	this->mode = mode;
	BlkList = Blk;
	TrmList = Trm;
	//Tstep
	cout << "Current Timestep: " << tStep << endl;
	//RDY
	cout << "---------------------     RDY processes   -----------------------" << endl;
	for (int i = 0; i < prcsrCount; i++) {
		cout << "processor " << i << " ";
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
			cout << *prcsrList[i] << "(P" << i+1 << "), ";
		}
	}
	cout << "\b\b";
	cout << endl;
	//TRM
	cout << "---------------------     TRM processes   -----------------------" << endl;
	cout << TrmList.GetCount() << " TRM: ";
	TrmList.printInfo();
	cout << endl;
	
	cout << "PRESS ANY KEY TO MOVE TO NEXT STEP!" << endl;
	system("pause > nul");
}

UI::~UI(){}