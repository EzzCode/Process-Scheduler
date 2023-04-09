#pragma once
#include "Processor.h"
class Scheduler;
class SJF :
	public Processor
{
private:
public:
	virtual void ScheduleAlgo();
};