#pragma once
#include "Processor.h"
class Scheduler;
class FCFS :
	public Processor
{
private:
	LinkedList<Process> RDY;
	Process* RUN;
	//state var has values: {0,1} which represent states: {BUSY, IDLE}
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
	virtual void printRDY();
	virtual void printRUN(ostream& os);
	~FCFS() {};
};