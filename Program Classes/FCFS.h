#pragma once
#include "Processor.h"
class Scheduler;
class FCFS :
	public Processor
{
private:
	LinkedList<Process> RDY;
	int MaxW;
public:
	FCFS(Scheduler* pSch);
	virtual void moveToRDY(Process* Rptr);
	virtual void moveToRUN();
	virtual void moveToBLK();
	virtual void moveToTRM(Process* p);
	virtual Process* steal();
	virtual void kill_orph();
	virtual void RDYKill(int pID);
	virtual void ScheduleAlgo();
	virtual void printRDY();
	virtual void UpdateState();
	void migrateToRR();

	~FCFS() {};
};