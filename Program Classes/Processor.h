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
public:
	Processor(Scheduler* pSch) { pScheduler = pSch; };
	virtual void ScheduleAlgo() = 0;
	virtual void moveToRDY(Process* Rptr) = 0;
	virtual void moveToRUN() = 0;
	virtual void moveToBLK() = 0;
	virtual void moveToTRM(Process* p) = 0;
	virtual void RDYKill(int pID) {}
	virtual int getQueueLength() = 0;
	virtual float getpUtil() = 0;
	virtual float getpLoad() = 0;
	virtual int getstate() = 0;
	virtual int getT_BUSY() = 0;
	virtual int getT_IDLE() = 0;
	virtual void printRDY() = 0;
	virtual void printRUN() = 0;
	virtual bool isRunning() = 0;
	virtual void UpdateState() = 0;			//Updates State
	virtual void TManager() = 0;			//Manages T_Busy and T_Idle for output statistics

	//RNG
	int RNG() {
		return (rand() % 100 + 1);
	}

	//Generate decision
	virtual int decide() {
		int rng = RNG();
		if (rng >= 1 && rng <= 15) {
			return 0;
		}
		else if (rng >= 20 && rng <= 30) {
			return 1;
		}
		else if (rng >= 50 && rng <= 60) {
			return 2;
		}
		else {
			return 3;
		}
	}

	virtual ~Processor() {};
};