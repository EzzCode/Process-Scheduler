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
		int RTF;						//Remaining Time to finish
		int MaxW;						//Maximum Wait time
		int STL;						//Steal Time
		int forkProb;
		int noProcesses;				//number of processes
		int ProcessorsCounter;			//just a counter for the creation
		int mode;						//print mode
		
		//statistics
		int KillCount;
		int ForkCount;
		int STLCount;
		int RTF_migCount;
		int MaxW_migCount;
		float AvgWT;
		float AvgRT;
		float AvgTRT;

		Processor* myProcessor;			// Processor ptr for processor creation
		Process* myProcess;				// process ptr for process creation
		LinkedQueue<Process> NewList;
		LinkedQueue<Process> BlkList;
		LinkedQueue<Process> TrmList;
		Processor** processorList;
		Processor* SQF;					// Processor ptr for shortest queue
		Processor* LQF;					// Processor ptr for longest queue

		int tSQF;						//Shortest queue finish time
		int tLQF;						//Longest queue finish time

		//SIGKILL Queue
		LinkedQueue<sigKill> killQ;
		sigKill* sigPtr;				// placeholder ptr 
		int sigkillTime , killID;
		
		//UI class
		UI ui;

		//Steal 
		float getSTL_limit();

		//SQF & LQF
		//The variable section decides which section of processors to search in
		//Section 0 is full loop, 1 is FCFS, 2 is SJF, 3 is RR
		void set_SQF_LQF(int section);
		int getSQF_time(int section);
		int getLQF_time(int section);
		
		//Statistics
		void setStats();
		float getAvgWT();
		float getAvgRT();
		float getAvgTRT();
		float getRTFpercent();
		float getMaxWpercent();
		float getForkedpercent();
		float getKillpercent();
		float getSTLpercent();


		//Private Simulation methods
		void initializeUI(int modeVal);
		void fileLoading();
		void NEWtoRDY();
		void RDYtoRUN();
		void RUNAlgo();
		void BLKAlgo();
		void Kill();
		void printTerminal();

public:
	Scheduler(int modeVal);
	void simulate();					//Simulator Fn.
	void fork(Process* parent);			//Fork
	void schedToTRM(Process* p);
	void schedToBLk(Process* p);
	int getTimeSlice();
	int getRTF();
	void Migrate(Process* pPtr, int processor);
	~Scheduler();

	//RNG
	int RNG();
};

