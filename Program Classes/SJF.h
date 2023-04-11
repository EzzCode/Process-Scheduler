#pragma once
#include "Processor.h"

class Scheduler;
class SJF :
	public Processor
{
private:
	PQueue RDY;
	Process* RUN;
	int state, Qtime, BUSY, T_IDLE;
public:
	SJF(Scheduler* pSch);
	virtual void moveToRDY(Process* Rptr);
	virtual void moveToRUN();
	virtual void moveToBLK();
	virtual void ScheduleAlgo();
	virtual float getpUtil();
	virtual int getstate();
	~SJF() {};
};