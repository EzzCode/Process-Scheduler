#include "Scheduler.h"
#include "FCFS.h"

FCFS::FCFS(Scheduler* pSch) :Processor(pSch)
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
	Qtime += Rptr->get_CT();
	Rptr->set_state(1);			//Process state: RDY
	RDY.InsertEnd(Rptr);
	state = 0;					//Processor is busy
}

void FCFS::moveToRUN()
{
	if (!RUN && state == 0) {
		RUN = RDY.GetHeadData();
		RUN->set_state(2);		//Process state: RUN
		if (RDY.GetCount() == 0) state = 1;
	}
}

void FCFS::moveToBLK() {
	RUN->set_state(3);			//Process state: BLK
	pScheduler->schedToBLk(RUN);
}

void FCFS::moveToTRM(Process* p) {
	Total_TRT += p->get_TRT();
	p->set_state(4);			//Process state: TRM
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
		//Commented because the BLKAlgo has been updated but here FCFS is still depending on probability
		/*Qtime -= RUN->get_CT();
		moveToBLK();
		RUN = nullptr;*/
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

	//Forking
	if(RUN) pScheduler->fork(RUN);
}

//Random RDY Kill
void FCFS::RDYKill(int pID) {
	Process* p = nullptr;
	bool canKill = RDY.sig_kill(pID, p);
	if (canKill) {
		Qtime -= p->get_CT();
		moveToTRM(p);
		if (RDY.GetCount() == 0) state = 1;
	}
}

int FCFS::getQueueLength()
{
	return Qtime;
}


float FCFS::getpUtil()
{
	return (float)T_BUSY / (T_BUSY + T_IDLE);
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
	cout << "[FCFS]" << ": " << RDY.GetCount() << " RDY: ";
	RDY.printInfo();
}

//Print RUN process
void FCFS::printRUN() {
	cout << *(RUN);
}

bool FCFS::isRunning()
{
	return (RUN != nullptr);
}

void FCFS::UpdateState()
{
	if (!RUN && RDY.GetCount()==0)
		state = 0;
	else
		state = 1;
}

void FCFS::TManager()
{
	if (state == 0)
		T_BUSY++;
	else
		T_IDLE++;
}