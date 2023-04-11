#include "RR.h"

RR::RR(Scheduler* pSch):Processor(pSch)
{
}

void RR::ScheduleAlgo()
{
}

void RR::moveToRDY(Process* Rptr)
{
	RDY.enqueue(Rptr);
}

void RR::moveToRUN()
{
	RDY.dequeue(RUN);
}

void RR::moveToBLK()
{
}

float RR::getpUtil()
{
	return (float)BUSY / (BUSY + T_IDLE);
}

int RR::getstate()
{
	return state;
}
