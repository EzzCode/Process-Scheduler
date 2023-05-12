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
}

void SJF::moveToTRM(Process* p)
{
	Total_TRT += p->get_TRT();
	p->set_state(4);
	pScheduler->schedToTRM(p);
}

void SJF::ScheduleAlgo()
{
	if (!RUN) return;
	if (BLKManager() == false)
	{
		if (RUN->get_timer() == 0)
		{
			moveToTRM(RUN);
			RUN = nullptr;
			Qtime--;
		}
		else
		RUN->set_timer(RUN->get_timer() - 1);
	}
	UpdateState();
	TManager();
}

bool SJF::BLKManager()
{
	IO* io;
	bool b = RUN->peek_io(io);
	if (b)
	{
		if (RUN->peek_io(io) && io->IO_R == 0)
		{
			Qtime = Qtime - RUN->get_timer();
			moveToBLK();
			RUN = nullptr;
			return true;
		}
		else
		{
			if (RUN->get_timer() == 0)
			{
				moveToTRM(RUN);
				RUN = nullptr;
				return true;
			}
		}
			if (RUN->peek_io(io))
				io->IO_R--;
			RUN->set_timer(RUN->get_timer() - 1);
			Qtime--;
			return true;
	}
	return false;
}

int SJF::getQueueLength()
{
	return Qtime;
}


float SJF::getpUtil()
{
	return (float)T_BUSY / (T_BUSY + T_IDLE);
}
float SJF::getpLoad()
{
	return (float)T_BUSY / Total_TRT;
}
int SJF::getstate()
{
	return state;
}

int SJF::getT_BUSY()
{
	return T_BUSY;
}

int SJF::getT_IDLE()
{
	return T_IDLE;
}


void SJF::printRDY() {
	cout << "[SJF ]" << ": " << RDY.GetCount() << " RDY: ";
	RDY.printInfo();
}

//Print RUN process
void SJF::printRUN() {
	cout << *(RUN);
}

bool SJF::isRunning()
{
	return (RUN != nullptr);
}

void SJF::UpdateState()
{
	if (!RUN && RDY.isEmpty())
		state = 1;
	else
		state = 0;
}

void SJF::TManager()
{
	if (state == 0)
		T_BUSY++;
	else
		T_IDLE++;
}