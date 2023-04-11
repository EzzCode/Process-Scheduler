#pragma once
#include <iostream>
#include "../DS Implementations/LinkedList.h"
#include "../DS Implementations/LinkedQueue.h"
#include "../DS Implementations/PQueue.h"

using namespace std;
class Scheduler;

class Processor
{
private:
	virtual void printRUN(ostream&) = 0;
protected:
	Scheduler* pScheduler;
public:
	Processor(Scheduler* pSch) { pScheduler = pSch; };
	virtual void ScheduleAlgo() = 0;
	virtual void moveToRDY(Process* Rptr) = 0;
	virtual void moveToRUN() = 0;
	virtual int getQueueLength() = 0;
	virtual float getpUtil() = 0;
	virtual int getstate() = 0;
	virtual void printRDY() = 0;
	friend ostream& operator<<(ostream& os, Processor& p) {
		p.printRUN(os);
		return os;
	}
	virtual ~Processor() {};
};