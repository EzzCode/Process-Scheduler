#pragma once
#include <iostream>
#include "../DS Implementations/LinkedList.h"
#include "../DS Implementations/LinkedQueue.h"
using namespace std;
class Scheduler;

class Processor
{
private:
public:
	virtual void ScheduleAlgo() = 0;
};