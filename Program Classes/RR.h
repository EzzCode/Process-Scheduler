#pragma once
#include "Processor.h"
class Scheduler;
class RR :
	public Processor
{
private:
	LinkedQueue<Process> RDY;
	Process* RUN;
  //state var has values: {0,1} which represent states: {BUSY, IDLE}
	int state;
	int Qtime;
	int T_BUSY;
	int T_IDLE;
public:
	RR(Scheduler* pSch);
	virtual void ScheduleAlgo();
	virtual void moveToRDY(Process* Rptr);
	virtual void moveToRUN();
	virtual void moveToBLK();
	virtual void moveToTRM();
	virtual int getQueueLength();
	virtual float getpUtil();
	virtual int getstate();
	virtual void printRDY();
	virtual void printRUN(ostream& os);
	~RR() {};
};