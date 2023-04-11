#include "Scheduler.h"

#include <fstream>

using namespace std;
Scheduler::Scheduler() 
{
	timeCounter = 0;
	NF = 0;
	NS = 0;
	NR = 0;
	timeSlice = 0;
	RTF = 0;
	MaxW = 0;
	STL = 0;
	forkProb = 0;
	noProcesses = 0;
	ProcessorsCounter = 0;
	processorList = nullptr;
	SQF = nullptr;
	LQF = nullptr;
	tSQF = -1;
	tLQF = -1;
}
void Scheduler::fileLoading()
{
	ifstream Infile("input.txt");
	Infile >>NF >>NS >>NR;
	processorList = new Processor * [NF + NS + NR];// alocate processor pointers 
	Infile >>timeSlice;
	Infile >>RTF >>MaxW >>STL >>forkProb;
	Infile >>noProcesses;
	//processes creation
	for (int i = 0; i < noProcesses; i++) 
	{
		myProcess = new Process();
		myProcess->Load(Infile);
		NewList.enqueue(myProcess);
	}
	// processor creation
	for (int i = 0; i < NF; i++)
	{
		myProcessor = new FCFS(this);
		processorList[ProcessorsCounter++] = myProcessor;
	}
	for (int i = 0; i < NS; i++)
	{
		myProcessor = new SJF(this);
		processorList[ProcessorsCounter] = myProcessor;
		ProcessorsCounter++;
	}
	for (int i = 0; i < NR; i++)
	{
		myProcessor = new RR(this);
		processorList[ProcessorsCounter] = myProcessor;
		ProcessorsCounter++;
	}
	//SigKill
	while (Infile>>sigkillTime>> killID)
	{
		sigPtr = new sigKill;
		sigPtr->tstep = sigkillTime;
		sigPtr->pID = killID;
		killQ.enqueue(sigPtr);
	}
}
//move to TRM fn
void Scheduler::schedToTRM(Process* p) 
{
	TrmList.enqueue(p);
}
//move to BLK fn
void Scheduler::schedToBLk(Process* p)
{
	BlkList.enqueue(p);
}
