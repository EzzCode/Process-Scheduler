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
	int state;
	int Qtime;
	int T_BUSY;
	int T_IDLE;
public:
	RR(Scheduler* pSch);
	virtual void ScheduleAlgo();
	virtual void moveToRDY(Process* Rptr);
	virtual void moveToRUN();
	virtual int getQueueLength();
	virtual float getpUtil();
	virtual int getstate();
	~RR() {};
};