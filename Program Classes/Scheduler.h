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
		int noProcessors;
		Processor* myProcessor;// Processor ptr for process creation
		Process* myProcess; // process ptr for process creation
		LinkedQueue NewList;
		LinkedQueue BlkList;
		LinkedQueue TrmLsit;
		// todo: list of processors
		Processor** processorList = new Processor * [NF+NS+NR];
		
public:
	Scheduler();
	void fileLoading();
};

