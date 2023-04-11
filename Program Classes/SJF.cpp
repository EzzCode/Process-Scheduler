#include "SJF.h"

SJF::SJF(Scheduler* pSch):Processor(pSch)
{
}

void SJF::moveToRDY(Process* Rptr)
{
}

void SJF::moveToRUN()
{
}

void SJF::moveToBLK()
{
}

void SJF::ScheduleAlgo()
{
}


float SJF::getpUtil()
{
	return (float)BUSY / (BUSY + T_IDLE);
}

int SJF::getstate()
{
	return state;
}