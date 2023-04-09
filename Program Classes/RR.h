#pragma once
#include "Processor.h"
class Scheduler;
class RR :
	public Processor
{
private:
	LinkedQueue RDY;
	Process* RUN;
	int pLoad, pUtil, state;
public:
	RR(Scheduler* pSch);
	virtual void ScheduleAlgo();
};