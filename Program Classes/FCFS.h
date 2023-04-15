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
	int state;
	int Qtime;
	int T_BUSY;
	int T_IDLE;
public:
	FCFS(Scheduler* pSch);
	virtual void moveToRDY(Process* Rptr);
	virtual void moveToRUN();
	virtual void moveToBLK();
	virtual void moveToTRM();
	virtual void ScheduleAlgo();
	virtual int getQueueLength();
	virtual float getpUtil();
	virtual int getstate();
	virtual void printRDY();
	virtual void printRUN(ostream& os);

	//Random RDY Kill
	virtual void RDYKill();

	~FCFS() {};
};