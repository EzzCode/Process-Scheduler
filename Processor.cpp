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

void Processor::ioAlgo(Process* RUN, int& Qtime)
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