#include "RR.h"

RR::RR(Scheduler* pSch):Processor(pSch)
{
	state = 0;
	Qtime = 0;
	T_BUSY = 0;
	T_IDLE = 0;
}

void RR::ScheduleAlgo()
{
}

void RR::moveToRDY(Process* Rptr)
{
	Qtime += Rptr->get_CT();
	RDY.enqueue(Rptr);
}

void RR::moveToRUN()
{
	RDY.dequeue(RUN);
	Qtime -= RUN->get_CT();
}

int RR::getQueueLength()
{
	return Qtime;
}


float RR::getpUtil()
{
	return (float)T_BUSY / (T_BUSY + T_IDLE);
}

int RR::getstate()
{
	return state;
}

void RR::printRDY() {
	cout << "[RR  ]" << ": " << RDY.GetCount() << " RDY: ";
	RDY.printInfo();
}

//Print RUN process
void RR::printRUN(ostream& os) {
	os << this->RUN;
}