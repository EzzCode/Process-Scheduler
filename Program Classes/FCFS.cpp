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
	if (!RUN && RDY.GetCount() != 0) {
		RUN = RDY.GetHeadData();
		RUN->set_state(2);		//Process state: RUN
		//if (RDY.GetCount() == 0) state = 1; commented bec outdated ~S
		UpdateState();
	}
}

void FCFS::moveToBLK() {
	RUN->set_state(3);			//Process state: BLK
	pScheduler->schedToBLk(RUN);
	RUN = nullptr;
	moveToRUN(); // to add another process in run
}

void FCFS::moveToTRM(Process* p) {
	Total_TRT += p->get_TRT();
	p->set_state(4);			//Process state: TRM
	//if removed prcss is the running move a prcss from RDY to Run
	if (p==RUN)
	{
		RUN = nullptr;
		pScheduler->schedToTRM(p);
		moveToRUN(); // to add another process in run
	}
	// if its not a running process
	else
	{
		pScheduler->schedToTRM(p);
	}
}

void FCFS::ScheduleAlgo()
{
    if (!RUN) {
        TManager();
        return;
    }
	// a check if process has ended because of a bizarre special case
	hasEnded(RUN);
	
	if (RUN) 
	{
		ioAlgo(RUN, Qtime);// how processor deals with IO
	}
	
	if (RUN) // i made this cond in case run was blk and no process to replace it 
	{
		hasEnded(RUN);
	}
	
	//Forking
	if (RUN) pScheduler->fork(RUN); //i commented it out for now 
	
	if (RUN)// i made this cond in case run was trm and no process to replace it 
	{
		
		RUN->set_timer(RUN->get_timer() - 1);
		Qtime--;
	}
	
	UpdateState();
    TManager();

}

//Random RDY Kill
void FCFS::RDYKill(int pID) {
	Process* p = nullptr;
	bool canKill = RDY.sig_kill(pID, p);
	if (canKill) {
		Qtime -= p->get_CT();
		moveToTRM(p);
		UpdateState();
	}
	if (RUN) 
	{
		if (RUN->get_PID() == pID)
		{
			Qtime -= RUN->get_CT();
			moveToTRM(RUN);
			UpdateState();
		}
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