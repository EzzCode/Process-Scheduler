#include "EDF.h"
#include "Scheduler.h"
EDF::EDF(Scheduler* pSch) :Processor(pSch)
{
	{
		state = 1;
		overheated = false;
		Qtime = 0;
		T_BUSY = 0;
		T_IDLE = 0;
		Total_TRT = 0;
		RUN = nullptr;
	}
}

void EDF::moveToRDY(Process* Rptr)
{
	int priority = Rptr->get_DD();
	Qtime += priority;
	Rptr->set_state(1);			//Process state: RDY
	RDY.enqueue(Rptr, priority);
	state = 0;					//Processor is busy
}

void EDF::moveToRUN()
{
	if (!RUN && RDY.isEmpty() == false) {
		RDY.dequeue(RUN);
		RUN->set_state(2);		//Process state: RUN
	}
	UpdateState();
}

void EDF::moveToBLK()
{
	RUN->set_state(3);
	pScheduler->schedToBLk(RUN);
	RUN = nullptr;
	moveToRUN(); // to add another process in run
}

void EDF::moveToTRM(Process* p)
{
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
	}
}

Process* EDF::steal()
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

void EDF::ScheduleAlgo()
{
	if (overheated) return;
	if (!RUN)
	{
		UpdateState();
		TManager();
		return;
	}
	hasEnded();

	if (RUN)						//if there is a process in RDY which has lower DD
	{
		Process* p = NULL;
		if (RDY.peek(p))
		{
			if (p->get_DD() < RUN->get_DD())
			{
				moveToRDY(RUN);
				RUN = NULL;
				moveToRUN();
			}
		}
	}
	//Following conditions in case RDY is empty
	if (RUN)
	{
		ioAlgo(Qtime);
	}
	if (RUN)
	{
		hasEnded();
	}
	if (RUN)
	{
		RUN->set_timer(RUN->get_timer() - 1);
		Qtime--;
	}

	UpdateState();
	TManager();
}

void EDF::printRDY()
{
	cout << "[EDF]" << ": " << RDY.GetCount() << " RDY: ";
	if (!overheated)
	{
		RDY.printInfo();
	}
	else
	{
		cout << "OVHT";
	}
}

void EDF::UpdateState()
{
	if (!RUN && RDY.isEmpty())
		state = 1;	// busy
	else
		state = 0;	// idle
}

int EDF::get_rdy_count()
{
	return RDY.GetCount();
}

void EDF::ovht_manager()
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
