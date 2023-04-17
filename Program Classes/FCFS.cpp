#include "Scheduler.h"
#include "FCFS.h"

FCFS::FCFS(Scheduler* pSch):Processor(pSch)
{
	state = 1;
	Qtime = 0;
	T_BUSY = 0;
	T_IDLE = 0;
	Total_TRT = 0;
	RUN = nullptr;
}

void FCFS::moveToRDY(Process* Rptr)
{
	Rptr->set_state(1);
	RDY.InsertEnd(Rptr);
}

void FCFS::moveToRUN()
{
	//If idle
	if (state == 1) {
		RUN = RDY.GetHeadData();
		if (RUN) {
			RUN->set_state(2);
			state = 0;
		}
	}
}

void FCFS::moveToBLK() {
	RUN->set_state(3);
	pScheduler->schedToBLk(RUN);
}

void FCFS::moveToTRM(Process* p) {
	Total_TRT += p->get_TRT();
	p->set_state(4);
	pScheduler->schedToTRM(p);
}

void FCFS::ScheduleAlgo()
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

//Random RDY Kill
void FCFS::RDYKill(int pID) {
	Process* p = nullptr;
	bool canKill = RDY.sig_kill(pID, p);
	if (canKill) {
		moveToTRM(p);
	}
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

int FCFS::getT_BUSY()
{
	return T_BUSY;
}
float FCFS::getpLoad()
{
	return (float)T_BUSY / Total_TRT;
}
int FCFS::getT_IDLE()
{
	return T_IDLE;
}

void FCFS::printRDY() {
	cout<< "[FCFS]" << ": " << RDY.GetCount() << " RDY: ";
	RDY.printInfo();
}

//Print RUN process
void FCFS::printRUN() {
	cout << *(RUN);
}

