#pragma once
#include <iostream>
#include "../DS Implementations/LinkedList.h"
#include "../DS Implementations/LinkedQueue.h"
using namespace std;
class Scheduler;

class Processor
{
protected:
	Scheduler* pScheduler;
public:
	Processor(Scheduler* pSch) { pScheduler = pSch; };
	virtual void ScheduleAlgo() = 0;
	virtual void moveToRDY() = 0;
	virtual void moveToRUN() = 0;
	virtual void moveToBLK() = 0;
	~Processor() {};
};