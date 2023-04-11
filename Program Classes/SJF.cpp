#include "SJF.h"

SJF::SJF(Scheduler* pSch):Processor(pSch)
{
	state = 0;
	Qtime = 0;
	T_BUSY = 0;
	T_IDLE = 0;
}

void SJF::moveToRDY(Process* Rptr)
{
}

void SJF::moveToRUN()
{
}
void SJF::ScheduleAlgo()
{
}

int SJF::getQueueLength()
{
	return Qtime;
}


float SJF::getpUtil()
{
	return (float)T_BUSY / (T_BUSY + T_IDLE);
}

int SJF::getstate()
{
	return state;
}

void SJF::printRDY() {
	cout << "[SJF ]" << ": " << "RDY.GetCount()" << " RDY: ";
	cout << "UNDER DEV";
}

//Print RUN process
void SJF::printRUN(ostream&) {
	cout << "UNDER DEV";
}