#pragma once

class Scheduler;
class SJF :
	public Processor
{
private:
	PQueue RDY;
public:
	SJF(Scheduler* pSch);
	virtual void moveToRDY(Process* Rptr);
	virtual void moveToRUN();
	virtual void moveToBLK();
	virtual void moveToTRM(Process* p);
	virtual Process* steal();
	virtual void ScheduleAlgo();
	virtual void printRDY();
	virtual void UpdateState();
	~SJF() {};
};