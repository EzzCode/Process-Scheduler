#include "Scheduler.h"
#include "SJF.h"

SJF::SJF(Scheduler* pSch):Processor(pSch)
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
	if (!RUN && RDY.isEmpty()==false) {
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
	IO* io;
	bool b = RUN->peek_io(io);
	switch (b)
	{
	case true:
		if (RUN->peek_io(io) && io->IO_R == 0)
		{
			Qtime=Qtime-RUN->get_timer();
			moveToBLK();
			RUN = nullptr;
			break;
		}
		else
		{
			if (RUN->get_timer() == 0)
			{
				moveToTRM(RUN);
				RUN = nullptr;
				break;
			}
		}
			if (RUN->peek_io(io))
				io->IO_R--;
			RUN->set_timer(RUN->get_timer() - 1);
			Qtime--;
		break;
	case false:
			if (RUN->get_timer() == 0)
			{
				moveToTRM(RUN);
				RUN = nullptr;
				break;
			}
				RUN->set_timer(RUN->get_timer() - 1);
				Qtime--;
			break;
	default:
		break;
	}
	UpdateState();
	TManager();
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
		state = 0;
	else
		state = 1;
}

void SJF::TManager()
{
	if (state == 0)
		T_BUSY++;
	else
		T_IDLE++;
}