#include "Scheduler.h"
#include "FCFS.h"

FCFS::FCFS(Scheduler* pSch) :Processor(pSch)
{
	state = 1;
	overheated = false;
	Qtime = 0;
	T_BUSY = 0;
	T_IDLE = 0;
	Total_TRT = 0;
	MaxW = pSch->getMaxW();
	RUN = nullptr;
}

Process* FCFS::steal()
{
	if (RDY.GetCount() != 0)
	{
		Process* s = RDY.GetHeadData();
		if (!s->has_parent())
		{
			Qtime -= s->get_timer();
			return s;
		}
		else
		{
			RDY.InsertBeg(s);
		}
	}
	return NULL;
}

void FCFS::migrateToRR()
{
	pScheduler->Migrate(RUN, 3);
	Qtime -= RUN->get_timer();
	RUN = NULL;
	moveToRUN();
}

int FCFS::get_rdy_count()
{
	return RDY.GetCount();
}

void FCFS::moveToRDY(Process* Rptr)
{
	Qtime += Rptr->get_timer();
	Rptr->set_state(1);			//Process state: RDY
	RDY.InsertEnd(Rptr);
	state = 0;					//Processor is busy
}

void FCFS::moveToRUN()
{
	if (!RUN && RDY.GetCount() != 0) {
		RUN = RDY.GetHeadData();
		RUN->set_state(2);		//Process state: RUN
		if(RUN->get_RT() == -1) pScheduler->calc_RT(RUN);
	}
	UpdateState();
}

void FCFS::moveToBLK() {
	RUN->set_state(3);			//Process state: BLK
	pScheduler->schedToBLk(RUN);
	RUN = nullptr;
	moveToRUN(); // to add another process in run
}

void FCFS::moveToTRM(Process* p) {
	//Total_TRT += p->get_TRT();
	p->set_state(4);			//Process state: TRM
	//if removed prcss is the running move a prcss from RDY to Run
	if (p == RUN)
	{
		RUN = nullptr;
		pScheduler->schedToTRM(p);
		Total_TRT += p->get_TRT();
		moveToRUN(); // to add another process in run
	}
	// if its not a running process 
	else
	{
		pScheduler->schedToTRM(p);
		Total_TRT += p->get_TRT();
	}
}

void FCFS::ScheduleAlgo()
{
	if (overheated) return;
	if (!RUN) {
		UpdateState();
		TManager();
		return;
	}
	// a check if process has ended because of a bizarre special case
	hasEnded();

	if (RUN)
	{
		ioAlgo(Qtime);// how processor deals with IO
	}
	if (RUN)
	{
		if (pScheduler->canMigrate(RUN,3))
		{
			migrateToRR();
		}
	}
	if (RUN)	// i made this cond in case run was blk and no process to replace it 
	{
		hasEnded();
	}

	//Forking
	if (RUN) pScheduler->fork(RUN);

	if (RUN)// i made this cond in case run was trm and no process to replace it 
	{
		RUN->set_timer(RUN->get_timer() - 1);
		Qtime--;
	}

	UpdateState();
	TManager();

}

// Search and kill orphans
void FCFS::kill_orph()
{
	Process* p;
	bool canKill = RDY.kill_prcs(-1, true, p);
	while (canKill)
	{
		Qtime -= p->get_timer();
		moveToTRM(p);
		canKill = RDY.kill_prcs(-1, true, p);
		UpdateState();
	}
	if (RUN)
	{
		if (RUN->get_state() == 5)
		{
			Qtime -= RUN->get_timer();
			moveToTRM(RUN);
			UpdateState();
		}
	}
}

// SigKill
bool FCFS::RDYKill(int pID) {
	Process* p = nullptr;
	bool canKill = RDY.kill_prcs(pID, false, p);
	if (canKill) {
		Qtime -= p->get_timer();
		moveToTRM(p);
		UpdateState();
		return true;
	}
	if (RUN)
	{
		if (RUN->get_PID() == pID)
		{
			Qtime -= RUN->get_timer();
			moveToTRM(RUN);
			UpdateState();
			return true;
		}
	}
	return false;
}

void FCFS::printRDY() {
	cout << "[FCFS]" << ": " << RDY.GetCount() << " RDY: ";
	if (!overheated)
	{
		RDY.printInfo();
	}
	else
	{
		cout << "OVHT";
	}
}

void FCFS::UpdateState()
{
	if (!RUN && RDY.GetCount() == 0)
		state = 1; // busy
	else
		state = 0; // idle
}

void FCFS::ovht_manager()
{
	// if process cant be transferred to another processor
	// process remains in RDY of current processor
	bool cleared = true;
	int count_rdy = RDY.GetCount();
	Process* ptr = nullptr;
	if (RUN)
	{
		cleared = pScheduler->clear_ovht_prcsr(RUN);
		if (cleared)
		{
			Qtime -= RUN->get_timer();
			RUN = nullptr;
		}
		else
		{
			Qtime -= RUN->get_timer();
			moveToRDY(RUN);
			RUN = nullptr;
		}
	}
	for (int i = 0; i < count_rdy; i++)
	{
		ptr = RDY.GetHeadData();
		cleared = pScheduler->clear_ovht_prcsr(ptr);
		if (!cleared)
		{
			Qtime -= ptr->get_timer();
			moveToRDY(ptr);
		}
		else
		{
			Qtime -= ptr->get_timer();
		}
	}
}