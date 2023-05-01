#include "Scheduler.h"
#include "SJF.h"

SJF::SJF(Scheduler* pSch):Processor(pSch)
{
	state = 1;
	Qtime = 0;
	T_BUSY = 0;
	T_IDLE = 0;
	Total_TRT = 0;
	RUN = nullptr;
}

void SJF::moveToRDY(Process* Rptr)
{
	int priority = Rptr->get_CT();
	Qtime += priority;
	Rptr->set_state(1);			//Process state: RDY
	RDY.enqueue(Rptr, priority);
	state = 0;					//Processor is busy
}

void SJF::moveToRUN()
{
	if (!RUN && state == 0) {
		RDY.dequeue(RUN);
		RUN->set_state(2);		//Process state: RUN
		if (RDY.GetCount() == 0) state = 1;
	}
}

void SJF::moveToBLK() {
	RUN->set_state(3);
	pScheduler->schedToBLk(RUN);
}

void SJF::moveToTRM(Process* p) {
	Total_TRT += p->get_TRT();
	p->set_state(4);
	pScheduler->schedToTRM(p);
}

void SJF::ScheduleAlgo()
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

int SJF::getQueueLength()
{
	return Qtime;
}


float SJF::getpUtil()
{
	return (float)T_BUSY / (T_BUSY + T_IDLE);
}
float SJF::getpLoad()
{
	return (float)T_BUSY / Total_TRT;
}
int SJF::getstate()
{
	return state;
}

int SJF::getT_BUSY()
{
	return T_BUSY;
}

int SJF::getT_IDLE()
{
	return T_IDLE;
}


void SJF::printRDY() {
	cout << "[SJF ]" << ": " << RDY.GetCount() << " RDY: ";
	RDY.printInfo();
}

//Print RUN process
void SJF::printRUN() {
	cout << *(RUN);
}

bool SJF::isRunning()
{
	return (RUN != nullptr);
}
