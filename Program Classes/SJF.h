#pragma once

class Scheduler;
class SJF :
	public Processor
{
private:
	PQueue RDY;
	Process* RUN;
  //state var has values: {0,1} which represent states: {BUSY, IDLE}
	int state;
	int Qtime;
	int T_BUSY;
	int T_IDLE;
	int Total_TRT;
public:
	SJF(Scheduler* pSch);
	virtual void moveToRDY(Process* Rptr);
	virtual void moveToRUN();
	virtual void moveToBLK();
	virtual void moveToTRM(Process* p);
	virtual void ScheduleAlgo();
	virtual int getQueueLength();
	virtual float getpUtil();
	virtual float getpLoad();
	virtual int getstate();
	virtual int getT_BUSY();
	virtual int getT_IDLE();
	virtual void printRDY();
	virtual void printRUN();
	~SJF() {};
};