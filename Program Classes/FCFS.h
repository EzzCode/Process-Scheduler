#pragma once
#include "Processor.h"
class Scheduler;
class FCFS :
	public Processor
{
private:
public:
	virtual void ScheduleAlgo();
};