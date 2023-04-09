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
};