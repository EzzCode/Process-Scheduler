#include "Scheduler.h"
#include "RR.h"

RR::RR(Scheduler* pSch) :Processor(pSch)
{
	state = 1;
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
		if (RUN->get_timer() < RTF)
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
	if (!RUN)
	{
		UpdateState();
		TManager();
		return;
	}

	if (RUN)
	{
		if (RUN->get_timer() == 0)
		{
			pScheduler->BeforeDDManager(RUN);
			hasEnded(RUN);
		}
	}

	//Following conditions in case RDY is empty
	if (RUN)
	{
		ioAlgo(RUN, Qtime);
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
		if (RUN->get_timer() == 0)
		{
			pScheduler->BeforeDDManager(RUN);
			hasEnded(RUN);
		}
	}
	if (RUN && RunTS > 0)
	{
		RUN->set_timer(RUN->get_timer() - 1);
		RunTS--;
		Qtime--;
	}
	else if (RUN && RunTS == 0)
	{
		moveToRDY(RUN);
		RUN = NULL;
	}

	UpdateState();
	TManager();
}

void RR::printRDY() {
	cout << "[RR ]" << ": " << RDY.GetCount() << " RDY: ";
	RDY.printInfo();
}

void RR::UpdateState()
{
	if (!RUN && RDY.isEmpty())
		state = 1;	// busy
	else
		state = 0;	// idle
}