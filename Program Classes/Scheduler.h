#pragma once
#include "Process.h"
#include "Processor.h"
#include "FCFS.h"
#include "RR.h"
#include "SJF.h"
#include "../DS Implementations/LinkedQueue.h"
#include "../DS Implementations/LinkedList.h"

class Scheduler
{
	private:
		int timeCounter;
		int NF;
		int NS;
		int NR;
		int timeSlice;
		int RTF;
		int MaxW;
		int STL;
		int forkProb;
		int noProcesses; // number of processes
		int ProcessorsCounter;//just a counter for the creation
		Processor* myProcessor;// Processor ptr for process creation
		Process* myProcess; // process ptr for process creation
		QueueADT NewList;
		QueueADT BlkList;
		QueueADT TrmLsit;
		Processor** processorList = new Processor * [NF+NS+NR];
		enum processorStates
		{
			idle
		};
		enum processStates {
			NEW,
			RDY,
			RUN,
			BLK,
			TRM
		};
public:
	Scheduler();
	void fileLoading();
};

