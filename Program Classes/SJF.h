#pragma once
#include "Processor.h"
class Scheduler;
class SJF :
	public Processor
{
private:
	Process* RUN;
	int pLoad, pUtil, state;
public:
	SJF(Scheduler* pSch);
	virtual void ScheduleAlgo();
};