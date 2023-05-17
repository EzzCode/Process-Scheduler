#include "Scheduler.h"
#include "RR.h"

RR::RR(Scheduler* pSch) :Processor(pSch)
{
	state = 1;
	overheated = false;
	Qtime = 0;
	T_BUSY = 0;
	T_IDLE = 0;
	Total_TRT = 0;
	TimeSlice = pSch->getTimeSlice();
	RunTS = 0;
	RTF = pSch->getRTF();
	RUN = nullptr;
}

Process* RR::steal()
{
	Process* s;
	if (RDY.isEmpty() == false)
	{
		RDY.dequeue(s);
		Qtime -= s->get_timer();
		return s;
	}
	return nullptr;
}

void RR::migrateToSJF()
{
	pScheduler->Migrate(RUN,2);
	Qtime -= RUN->get_timer();
	RUN = NULL;
	moveToRUN();
}

int RR::get_rdy_count()
{
	return RDY.GetCount();
}

void RR::moveToRDY(Process* Rptr)
{
	Qtime += Rptr->get_timer();
	Rptr->set_state(1);			//Process state: RDY
	RDY.enqueue(Rptr);
	state = 0;					//Processor is busy
}

void RR::moveToRUN()
{
	if (!RUN && RDY.isEmpty() == false) {
		RDY.dequeue(RUN);
		if (RUN->get_RT() == -1) pScheduler->calc_RT(RUN);
		if (pScheduler->canMigrate(RUN,2))
		{
			migrateToSJF();
			return;
		}
		RUN->set_state(2);		//Process state: RUN
		RunTS = TimeSlice;
	}
	UpdateState();
}

void RR::moveToBLK()
{
	RUN->set_state(3);			//Process state: BLK
	pScheduler->schedToBLk(RUN);
	RUN = nullptr;
	moveToRUN(); // to add another process in run
}

void RR::moveToTRM(Process* p) {
	//Total_TRT += p->get_TRT();
	p->set_state(4);			//Process state: TRM
	pScheduler->schedToTRM(p);
	Total_TRT += p->get_TRT();
	RUN = nullptr;
	moveToRUN(); // to add another process in run
}

void RR::ScheduleAlgo()
{
	if (overheated) return;
	if (!RUN)
	{
		UpdateState();
		TManager();
		return;
	}
	hasEnded();

	//Following conditions in case RDY is empty
	if (RUN)
	{
		ioAlgo(Qtime);
	}
	if (RUN)
	{
		if (pScheduler->canMigrate(RUN,2))
		{
			migrateToSJF();
		}
	}
	if (RUN)
	{
		hasEnded();
	}
	if (RUN && RunTS > 0)
	{
		RUN->set_timer(RUN->get_timer() - 1);
		RunTS--;
		Qtime--;
	}
	else if (RUN && RunTS == 0)
	{
		Qtime -= RUN->get_timer();
		moveToRDY(RUN);
		RUN = NULL;
	}

	UpdateState();
	TManager();
}

void RR::printRDY() {
	cout << "[RR ]" << ": " << RDY.GetCount() << " RDY: ";
	if (!overheated)
	{
		RDY.printInfo();
	}
	else
	{
		cout << "OVHT";
	}
}

void RR::UpdateState()
{
	if (!RUN && RDY.isEmpty())
		state = 1;	// busy
	else
		state = 0;	// idle
}

void RR::ovht_manager()
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
		RDY.dequeue(ptr);
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