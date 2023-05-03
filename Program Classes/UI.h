#pragma once
#include "Process.h"
#include "Processor.h"
#include "FCFS.h"
#include "RR.h"
#include "SJF.h"
#include "../DS Implementations/LinkedQueue.h"
#include "../DS Implementations/LinkedList.h"
#include "../DEFS.h"
#include <thread>
#include <chrono>
class UI
{
private:
	//0 is Interactive mode
	//1 is Step-By-Step mode
	//2 is Silent mode
	int mode;
public:
	UI();
	void set_mode(int val);
	void updateTerminal(int timestep, Processor** processorList, int processorCount, LinkedQueue<Process>& Blk, LinkedQueue<Process>& Trm);
	void print_end();
	~UI();
};

