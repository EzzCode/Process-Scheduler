#pragma once
#include "Processor.h"
class Scheduler;
class FCFS :
	public Processor
{
private:
	LinkedList RDY;
	Process* RUN;
	float pLoad, pUtil;
	int state;
public:
	FCFS(Scheduler* pSch);
	virtual void ScheduleAlgo();
};