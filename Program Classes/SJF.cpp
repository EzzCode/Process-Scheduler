#include "Scheduler.h"
#include "SJF.h"

SJF::SJF(Scheduler* pSch):Processor(pSch)
{
	state = 1;
	Qtime = 0;
	T_BUSY = 0;
	T_IDLE = 0;
}

void SJF::moveToRDY(Process* Rptr)
{
	Qtime += Rptr->get_CT();
	int priority = Rptr->get_CT();
	RDY.enqueue(Rptr, priority);
}

void SJF::moveToRUN()
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

void SJF::moveToBLK() {
	pScheduler->schedToBLk(RUN);
}

void SJF::moveToTRM() {
	pScheduler->schedToTRM(RUN);
}


void SJF::ScheduleAlgo()
{
	if (!RUN) return;
	int choice = decide();
	//0 -> go BLK, 1 -> go RDY, 2 -> go TRM, 3 -> stay RUN
	switch (choice)
	{
	case 0:
		moveToBLK();
		state = 1;
		break;
	case 1:
		Qtime -= RUN->get_CT();
		moveToRDY(RUN);
		state = 1;
		break;
	case 2:
		moveToTRM();
		state = 1;
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

int SJF::getstate()
{
	return state;
}

void SJF::printRDY() {
	cout << "[SJF ]" << ": " << RDY.GetCount() << " RDY: ";
	RDY.printInfo();
}

//Print RUN process
void SJF::printRUN(ostream& os) {
	os << *(RUN);
}