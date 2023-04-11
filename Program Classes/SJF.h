#pragma once
#include "Processor.h"

class Scheduler;
class SJF :
	public Processor
{
private:
	PQueue RDY;
	Process* RUN;
	int state;
	int Qtime;
	int T_BUSY;
	int T_IDLE;
public:
	SJF(Scheduler* pSch);
	virtual void moveToRDY(Process* Rptr);
	virtual void moveToRUN(); 
	virtual void ScheduleAlgo();
	virtual int getQueueLength();
	virtual float getpUtil();
	virtual int getstate();
	~SJF() {};
};