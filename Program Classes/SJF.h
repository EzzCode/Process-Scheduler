#pragma once
#include "Processor.h"

class Scheduler;
class SJF :
	public Processor
{
private:
	Process* RUN;
	float pLoad, pUtil;
	int state;
public:
	SJF(Scheduler* pSch);
	virtual void moveToRDY(Process* Rptr);
	virtual void moveToRUN();
	virtual void moveToBLK();
	virtual void ScheduleAlgo();
	~SJF() {};
};