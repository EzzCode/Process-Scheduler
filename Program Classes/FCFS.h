#pragma once
#include "Processor.h"
class Scheduler;
class FCFS :
	public Processor
{
private:
	LinkedList RDY;
	Process* RUN;
	int state, TRT, BUSY, T_IDLE;
public:
	FCFS(Scheduler* pSch);
	virtual void moveToRDY(Process* Rptr);
	virtual void moveToRUN();
	virtual void moveToBLK();
	virtual void ScheduleAlgo();
	virtual float getpLoad();
	virtual float getpUtil();
	virtual int getstate();
	~FCFS() {};
};