#pragma once
#include "Processor.h"
class Scheduler;
class FCFS :
	public Processor
{
private:
	LinkedList<Process> RDY;
	Process* RUN;
	int state, Qtime, BUSY, T_IDLE;
public:
	FCFS(Scheduler* pSch);
	virtual void moveToRDY(Process* Rptr);
	virtual void moveToRUN();
	virtual void moveToBLK();
	virtual void ScheduleAlgo();
	virtual float getpUtil();
	virtual int getstate();
	~FCFS() {};
};