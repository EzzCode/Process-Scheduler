#pragma once
#include "Process.h"
#include "../DS Implementations/LinkedList.h"
#include "../DS Implementations/LinkedQueue.h"
#include "../DS Implementations/PQueue.h"

using namespace std;
class Scheduler;

class Processor
{
private:

	//Assist << operator overload
	virtual void printRUN(ostream&) = 0;
protected:
	Scheduler* pScheduler;
public:
	Processor(Scheduler* pSch) { pScheduler = pSch; };
	virtual void ScheduleAlgo() = 0;
	virtual void moveToRDY(Process*& Rptr) = 0;
	virtual void moveToRUN() = 0;
	virtual void moveToBLK() = 0;
	virtual void moveToTRM() = 0;
	virtual int getQueueLength() = 0;
	virtual float getpUtil() = 0;
	virtual int getstate() = 0;
	virtual void printRDY() = 0;

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

	//Random RDY Kill
	virtual void RDYKill() {}

	//Print RUN
	friend ostream& operator<<(ostream& os, Processor*& p) {
		p->printRUN(os);
		return os;
	}
	virtual ~Processor() {};
};