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
		LinkedQueue NewList;
		LinkedQueue BlkList;
		LinkedQueue TrmLsit;
		Processor** processorList;
		Processor* SQF;
		Processor* LQF;
		int tSQF;
		int tLQF;
		enum processorStates
		{
			idle,
			busy
		};
		enum processStates {
			NEW,
			RDY,
			RUN,
			BLK,
			TRM,
			ORPH
		};
public:
	Scheduler();
	void fileLoading();
};

