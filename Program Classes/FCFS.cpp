#include "Scheduler.h"
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
	//If idle
	if (state == 1) {
		RUN = RDY.GetHeadData();
		if (RUN) {
			//Qtime -= RUN->get_CT();
			state = 0;
		}
	}
}

void FCFS::moveToBLK() {
	pScheduler->schedToBLk(RUN);
}

void FCFS::moveToTRM() {
	Total_TRT += RUN->get_TRT();
	pScheduler->schedToTRM(RUN);
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
void FCFS::printRUN(ostream& os) {
	os << *(RUN);
}

//Random RDY Kill
void FCFS::RDYKill() {
	Process* p;
	int randNum = RNG();
	bool canPeek = RDY.GetCount() > 0;
	if (canPeek) {
		for (int i = 0; i < RDY.GetCount() % randNum; i++) {
			//code
		}
	}
}