#include "Scheduler.h"
#include "RR.h"

RR::RR(Scheduler* pSch):Processor(pSch)
{
	state = 1;
	Qtime = 0;
	T_BUSY = 0;
	T_IDLE = 0;
	Total_TRT = 0;
	RUN = nullptr;
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
		moveToRDY(RUN);
		RUN = nullptr;
		state = 1;
		break;
	case 2:
		moveToTRM(RUN);
		RUN = nullptr;
		state = 1;
		break;
	default:
		break;
	}
}

void RR::moveToRDY(Process* Rptr)
{
	Rptr->set_state(1);
	RDY.enqueue(Rptr);
}

void RR::moveToRUN()
{
	//If idle
	if (state == 1) {
		bool check = RDY.dequeue(RUN);
		if (check) {
			RUN->set_state(2);
			state = 0;
		}
	}
}

void RR::moveToBLK() {
	RUN->set_state(3);
	pScheduler->schedToBLk(RUN);
}

void RR::moveToTRM(Process* p) {
	Total_TRT += p->get_TRT();
	p->set_state(4);
	pScheduler->schedToTRM(p);
}

int RR::getQueueLength()
{
	return Qtime;
}


float RR::getpUtil()
{
	return (float)T_BUSY / (T_BUSY + T_IDLE);
}

float RR::getpLoad()
{
	return (float)T_BUSY / Total_TRT;
}

int RR::getstate()
{
	return state;
}

int RR::getT_BUSY()
{
	return T_BUSY;
}
int RR::getT_IDLE()
{
	return T_IDLE;
}

void RR::printRDY() {
	cout << "[RR  ]" << ": " << RDY.GetCount() << " RDY: ";
	RDY.printInfo();
}

//Print RUN process
void RR::printRUN() {
	cout << *(RUN);
}