#pragma once
#include "Scheduler.h"
class UI
{
private:
	int tStep;
	int runCount;
	int prcsrCount;
	int mode;
	bool isRunning;
	Processor** prcsrList;
	LinkedQueue<Process> BlkList;
	LinkedQueue<Process> TrmList;
public:
	UI();
	void updateTerminal(int timestep, Processor** processorList, int processorCount, LinkedQueue<Process>& Blk, LinkedQueue<Process>& Trm, int mode);
	~UI();
};

