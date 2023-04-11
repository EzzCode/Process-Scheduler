#pragma once
#include "Processor.h"
#include "Process.h"
class Scheduler;
class RR :
	public Processor
{
private:
	LinkedQueue<Process> RDY;
	Process* RUN;
	int state, Qtime, BUSY, T_IDLE;
public:
	RR(Scheduler* pSch);
	virtual void ScheduleAlgo();
	virtual void moveToRDY(Process* Rptr);
	virtual void moveToRUN();
	virtual void moveToBLK();
	virtual float getpUtil();
	virtual int getstate();
	~RR() {};
};