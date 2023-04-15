#include "Scheduler.h"
#include "RR.h"

RR::RR(Scheduler* pSch):Processor(pSch)
{
	state = 1;
	Qtime = 0;
	T_BUSY = 0;
	T_IDLE = 0;
}

void RR::ScheduleAlgo()
{
	if (!RUN) return;
	int choice = decide();
	//0 -> go BLK, 1 -> go RDY, 2 -> go TRM, 3 -> stay RUN
	switch (choice)
	{
	case 0:
		moveToBLK();
		RUN = nullptr;
		state = 1;
		break;
	case 1:
		Qtime -= RUN->get_CT();
		moveToRDY(RUN);
		RUN = nullptr;
		state = 1;
		break;
	case 2:
		moveToTRM();
		RUN = nullptr;
		state = 1;
		break;
	default:
		break;
	}
}

void RR::moveToRDY(Process* Rptr)
{
	Qtime += Rptr->get_CT();
	RDY.enqueue(Rptr);
}

void RR::moveToRUN()
{
	//If idle
	if (state == 1) {
		bool check = RDY.dequeue(RUN);
		if (check) {
			//Qtime -= RUN->get_CT();
			state = 0;
		}
	}
}

void RR::moveToBLK() {
	pScheduler->schedToBLk(RUN);
}

void RR::moveToTRM() {
	pScheduler->schedToTRM(RUN);
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
	os << *(RUN);
}