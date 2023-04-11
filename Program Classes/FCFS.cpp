#include "FCFS.h"

FCFS::FCFS(Scheduler* pSch):Processor(pSch)
{
	state = 1;
	Qtime = 0;
	T_BUSY = 0;
	T_IDLE = 0;
}

void FCFS::moveToRDY(Process* Rptr)
{
	Qtime += Rptr->get_CT();
	RDY.InsertEnd(Rptr);
}

void FCFS::moveToRUN()
{
	RUN=RDY.GetHeadData();
	Qtime -= RUN->get_CT();
}


void FCFS::ScheduleAlgo()
{
}

int FCFS::getQueueLength()
{
	return Qtime;
}


float FCFS::getpUtil()
{
	return (float)T_BUSY/(T_BUSY + T_IDLE);
}

int FCFS::getstate()
{
	return state;
}

void FCFS::printRDY() {
	cout<< "[FCFS]" << ": " << RDY.GetCount() << " RDY: ";
	RDY.printInfo();
}

//Print RUN process
void FCFS::printRUN(ostream& os) {
	os << this->RUN;
}