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
void RR::migrateToSJF(Process* Rptr)
{
	pScheduler->Migrate(Rptr, 2);
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
		RUN->set_state(2);		//Process state: RUN
		if (RUN->get_timer() > RTF)
		{
			migrateToSJF(RUN);
		}
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
	Total_TRT += p->get_TRT();
	p->set_state(4);			//Process state: TRM
	pScheduler->schedToTRM(p);
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

	hasEnded(RUN);

	//Following conditions in case RDY is empty
	if (RUN)
	{
		ioAlgo(RUN, Qtime);
	}
	if (RUN)
	{
		if (RUN->get_timer() > RTF)
		{
			migrateToSJF(RUN);
		}
	}
	if (RUN)
	{
		hasEnded(RUN);
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

void RR::UpdateState()
{
	if (!RUN && RDY.isEmpty())
		state = 1;
	else
		state = 0;
}

void RR::TManager()
{
	if (state == 0)
		T_BUSY++;
	else
		T_IDLE++;
}

