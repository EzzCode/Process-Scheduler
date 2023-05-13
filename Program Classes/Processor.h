#pragma once
#include "Process.h"
#include "../DS Implementations/LinkedList.h"
#include "../DS Implementations/LinkedQueue.h"
#include "../DS Implementations/PQueue.h"

using namespace std;
class Scheduler;

class Processor
{
protected:
	Scheduler* pScheduler;
	int T_BUSY;
	int T_IDLE;
	int Total_TRT;
	int Qtime;
	int state;		 //state var has values: {0,1} which represent states: {BUSY, IDLE}
	Process* RUN = nullptr;
public:
	Processor(Scheduler* pSch) { pScheduler = pSch; };
	virtual void ScheduleAlgo() = 0;
	virtual void moveToRDY(Process* Rptr) = 0;
	virtual void moveToRUN() = 0;
	virtual void moveToBLK() = 0;
	virtual void moveToTRM(Process* p) = 0;
	virtual void kill_orph() {}	//To kill orphans in FCFS
	virtual Process* steal() = 0;
	virtual void printRDY() = 0;
	virtual void UpdateState() = 0;			//Updates State
	virtual void RDYKill(int pID) {}
	
	int getstate()
	{
		return state;
	}
	int getT_BUSY()
	{
		return T_BUSY;
	}
	int getT_IDLE()
	{
		return T_IDLE;
	}
	int getQueueLength()
	{
		return Qtime;
	}
	float getpUtil()
	{
		return (float)T_BUSY / (T_BUSY + T_IDLE);
	}
	float getpLoad()
	{
		return (float)T_BUSY /Total_TRT;
	}
	
	bool isRunning()
	{
		return (RUN != nullptr);
	}
	//Print RUN process
	void printRUN() {
		cout << *(RUN);
	}
	//IO Algo	
	void ioAlgo(Process* RUN,int & Qtime) 
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
	void setTotalTRT(int total)
	{
		Total_TRT = total;
	}
	int getTotalTRT()
	{
		return Total_TRT;
	}
	//Checks if Running process is finished
	void hasEnded(Process* RUN) 
	{
		if (RUN->get_timer() == 0) {
			moveToTRM(RUN);
		}
	}
	//RNG
	int RNG() {
		return (rand() % 100 + 1);
	}
	//Manages T_Busy and T_Idle for output statistics
	void TManager()
	{
		if (state == 0)
			T_BUSY++;
		else
			T_IDLE++;
	}
	 
	virtual ~Processor() {};
};