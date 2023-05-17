#include "Program Classes/Processor.h"
#include "Program Classes/Scheduler.h"

void Processor::hasEnded()
{
	if (RUN->get_timer() == 0) {
		pScheduler->BeforeDDManager(RUN);
		moveToTRM(RUN);
	}
}

int Processor::getstate()
{
	return state;
}

int Processor::getT_BUSY()
{
	return T_BUSY;
}

int Processor::getT_IDLE()
{
	return T_IDLE;
}

int Processor::getQueueLength()
{
	return Qtime;
}

float Processor::getpUtil()
{
	return (float)T_BUSY / (T_BUSY + T_IDLE);
}

float Processor::getpLoad()
{
	return (float)T_BUSY / Total_TRT;
}

bool Processor::isRunning()
{
	return (RUN != nullptr);
}

void Processor::printRUN()
{
	cout << *(RUN);
}

void Processor::ioAlgo(int& Qtime)
{
	IO* io;
	bool b = RUN->peek_io(io);
	if (b) {
		if (io->IO_R == 0) {
			Qtime = Qtime - RUN->get_timer();
			moveToBLK();

		}
		else {
			io->IO_R--;
		}
	}
}

void Processor::setTotalTRT(int total)
{
	Total_TRT = total;
}

int Processor::getTotalTRT()
{
	return Total_TRT;
}

int Processor::RNG()
{
	return (rand() % 100 + 1);
}

void Processor::TManager()
{
	if (state == 0)
		T_BUSY++;
	else
		T_IDLE++;
}

bool Processor::is_overheated()
{
	return overheated;
}

void Processor::set_overheat(bool status, int ovht_tSteps)
{
	overheated = status;
	if (overheated)
	{
		rem_ovht_tSteps = ovht_tSteps;
		ovht_manager();	// calls overheat manager to clear the queue of the processor
	}
}

int Processor::get_rem_ovht_steps()
{
	return rem_ovht_tSteps;
}

void Processor::decrement_ovht_steps()
{
	rem_ovht_tSteps--;
}