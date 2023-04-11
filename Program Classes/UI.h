#pragma once
#include "Process.h"
#include "Processor.h"
#include "FCFS.h"
#include "RR.h"
#include "SJF.h"
#include "../DS Implementations/LinkedQueue.h"
#include "../DS Implementations/LinkedList.h"
#include "../DEFS.h"
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
	void PrintScreen();
public:
	UI();
	void set_mode(int val);
	void updateTerminal(int timestep, Processor** processorList, int processorCount, LinkedQueue<Process>& Blk, LinkedQueue<Process>& Trm);
	~UI();
};

