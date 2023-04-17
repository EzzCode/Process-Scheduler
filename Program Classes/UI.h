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
	int mode;
public:
	UI();
	void set_mode(int val);
	void updateTerminal(int timestep, Processor** processorList, int processorCount, LinkedQueue<Process>& Blk, LinkedQueue<Process>& Trm);
	~UI();
};

