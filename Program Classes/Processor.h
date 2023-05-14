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
	void hasEnded();
	
	int getstate();
	int getT_BUSY();
	int getT_IDLE();
	int getQueueLength();
	float getpUtil();
	float getpLoad();
	
	bool isRunning();
	//Print RUN process
	void printRUN();
	//IO Algo	
	void ioAlgo(Process* RUN, int& Qtime);
	void setTotalTRT(int total);
	int getTotalTRT();
	//Checks if Running process is finished
	
	//RNG
	int RNG();
	//Manages T_Busy and T_Idle for output statistics
	void TManager();
	 
	virtual ~Processor() {}
};