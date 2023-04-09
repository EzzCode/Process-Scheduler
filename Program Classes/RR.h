#pragma once
#include "Processor.h"
class Scheduler;
class RR :
	public Processor
{
private:
public:
	virtual void ScheduleAlgo();
};