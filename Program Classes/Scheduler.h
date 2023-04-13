#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Process.h"
#include "Processor.h"
#include "FCFS.h"
#include "RR.h"
#include "SJF.h"
#include "../DS Implementations/LinkedQueue.h"
#include "../DS Implementations/LinkedList.h"
#include "../DEFS.h"
#include "UI.h"
class Scheduler
{
	private:
		int timeStep;
		int NF;
		int NS;
		int NR;
		int timeSlice;
		int RTF;
		int MaxW;
		int STL;
		int forkProb;
		int noProcesses;		//number of processes
		int ProcessorsCounter;	//just a counter for the creation
		int mode;				//set print mode

		//To keep track of the upcoming processor
		int processorIdx;

		Processor* myProcessor;// Processor ptr for process creation
		Process* myProcess; // process ptr for process creation
		LinkedQueue<Process> NewList;
		LinkedQueue<Process> BlkList;
		LinkedQueue<Process> TrmList;
		Processor** processorList;
		Processor* SQF;
		Processor* LQF;

		int tSQF;
		int tLQF;

		//SIGKILL Queue
		LinkedQueue<sigKill> killQ;
		sigKill* sigPtr; // placeholder ptr 
		int sigkillTime , killID;
		
		//UI class
		UI ui;

		//Private Simulation methods
		void initializeUI(int modeVal);
		void fileLoading();
		void NEWtoRDY();
		void RDYtoRUN();
		void RUNAlgo();
		void BLKAlgo();
		void randKill();
		void printTerminal();
		void properTerminate();

public:
	Scheduler(int modeVal);
	void simulate();	//Simple Simulator Fn.
	void schedToTRM(Process*& p);
	void schedToBLk(Process*& p);

	//RNG
	int RNG();
};

