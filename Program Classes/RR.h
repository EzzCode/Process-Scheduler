#pragma once
#include "Processor.h"
class Scheduler;
class RR :
	public Processor
{
private:
	LinkedQueue<Process> RDY;
	int TimeSlice;
	int RunTS;
	int RTF;
public:
	RR(Scheduler* pSch);
	virtual void ScheduleAlgo();
	virtual void moveToRDY(Process* Rptr);
	virtual void moveToRUN();
	virtual void moveToBLK();
	virtual void moveToTRM(Process* p);
	virtual Process* steal();
	virtual void printRDY();
	virtual void UpdateState();
	void migrateToSJF();
	virtual int get_rdy_count();
	// overheat manager
	virtual void ovht_manager();
	~RR() {};
};