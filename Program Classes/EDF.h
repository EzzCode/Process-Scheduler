#pragma once
#include "Processor.h"
class Scheduler;
class EDF : public Processor
{
private:
	PQueue RDY;
public:
	EDF(Scheduler* pSch);
	virtual void moveToRDY(Process* Rptr);
	virtual void moveToRUN();
	virtual void moveToBLK();
	virtual void moveToTRM(Process* p);
	virtual Process* steal();
	virtual void ScheduleAlgo();
	virtual void printRDY();
	virtual void UpdateState();
	virtual int get_rdy_count();
	virtual void ovht_manager();	// overheat manager
	~EDF() {};
};

