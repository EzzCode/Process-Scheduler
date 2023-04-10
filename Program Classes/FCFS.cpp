#include "FCFS.h"

FCFS::FCFS(Scheduler* pSch):Processor(pSch)
{
}

void FCFS::moveToRDY(Process* Rptr)
{
	RDY.InsertEnd(Rptr);
}

void FCFS::moveToRUN()
{
	RUN=RDY.GetHeadData();
}

void FCFS::moveToBLK()
{
}

void FCFS::ScheduleAlgo()
{
}
