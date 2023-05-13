#include "Scheduler.h"
#include "SJF.h"

SJF::SJF(Scheduler* pSch) :Processor(pSch)
{
	state = 1;
	Qtime = 0;
	T_BUSY = 0;
	T_IDLE = 0;
	Total_TRT = 0;
	RUN = nullptr;
}

Process* SJF::steal()
{
	Process* s;
	if (RDY.isEmpty() == false) {
		RDY.dequeue(s);
		return s;
	}
	return nullptr;
}

void SJF::moveToRDY(Process* Rptr)
{
	int priority = Rptr->get_timer();
	Qtime += priority;
	Rptr->set_state(1);			//Process state: RDY
	RDY.enqueue(Rptr, priority);
	state = 0;					//Processor is busy
}

void SJF::moveToRUN()
{
	if (!RUN && RDY.isEmpty() == false) {
		RDY.dequeue(RUN);
		RUN->set_state(2);		//Process state: RUN
	}
	UpdateState();
}

void SJF::moveToBLK()
{
	RUN->set_state(3);
	pScheduler->schedToBLk(RUN);
	RUN = nullptr;
	moveToRUN(); // to add another process in run
}

void SJF::moveToTRM(Process* p)
{
	Total_TRT += p->get_TRT();
	p->set_state(4);			//Process state: TRM
	//if removed prcss is the running move a prcss from RDY to Run
	if (p == RUN)
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

void SJF::ScheduleAlgo()
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
		hasEnded(RUN);
	}
	if (RUN)
	{
		RUN->set_timer(RUN->get_timer() - 1);
		Qtime--;
	}

	UpdateState();
	TManager();
}

void SJF::printRDY() {
	cout << "[SJF ]" << ": " << RDY.GetCount() << " RDY: ";
	RDY.printInfo();
}

void SJF::UpdateState()
{
	if (!RUN && RDY.isEmpty())
		state = 1;
	else
		state = 0;
}