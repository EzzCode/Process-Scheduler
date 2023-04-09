#include "FCFS.h"

FCFS::FCFS(Scheduler* pSch):Processor(pSch)
{
}

void FCFS::moveToRDY(Process* Rptr)
{
	RDY.InsertEnd(Rptr);
}

void FCFS::moveToRUN(Process* Rptr)
{
	RUN = Rptr;
	RDY.DeleteNode(Rptr);
}

void FCFS::moveToBLK()
{
}

void FCFS::ScheduleAlgo()
{
}
