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
	int Total_TRT;
public:
	RR(Scheduler* pSch);
	virtual void ScheduleAlgo();
	virtual void moveToRDY(Process* Rptr);
	virtual void moveToRUN();
	virtual void moveToBLK();
	virtual void moveToTRM(Process* p);
	virtual int getQueueLength();
	virtual float getpUtil();
	virtual float getpLoad();
	virtual int getstate();
	virtual int getT_BUSY();
	virtual int getT_IDLE();
	virtual void printRDY();
	virtual void printRUN();
	~RR() {};
};