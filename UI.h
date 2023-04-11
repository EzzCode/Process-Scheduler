#pragma once
#include "Program Classes/Scheduler.h"
class UI
{
private:
	int timestep;
	Processor** processorList;
	LinkedQueue<Process> BlkList;
	LinkedQueue<Process> TrmLsit;
public:
};

