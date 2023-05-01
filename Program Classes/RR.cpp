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

void RR::moveToRDY(Process* Rptr)
{
	Qtime += Rptr->get_CT();
	Rptr->set_state(1);			//Process state: RDY
	RDY.enqueue(Rptr);
	state = 0;					//Processor is busy
}

void RR::moveToRUN()
{
	if (!RUN && state == 0) {
		RDY.dequeue(RUN);
		RUN->set_state(2);		//Process state: RUN
		if (RDY.GetCount() == 0) state = 1;
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

void RR::ScheduleAlgo()
{
	if (!RUN) return;
	int choice = decide();
	//0 -> go BLK, 1 -> go RDY, 2 -> go TRM, 3 -> stay RUN
	switch (choice)
	{
	case 0:
		Qtime -= RUN->get_CT();
		moveToBLK();
		RUN = nullptr;
		break;
	case 1:
		Qtime -= RUN->get_CT();
		moveToRDY(RUN);
		RUN = nullptr;
		break;
	case 2:
		Qtime -= RUN->get_CT();
		moveToTRM(RUN);
		RUN = nullptr;
		break;
	default:
		break;
	}
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

bool RR::isRunning()
{
	return (RUN != nullptr);
}
