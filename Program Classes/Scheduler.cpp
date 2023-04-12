#include "Scheduler.h"

#include <fstream>

using namespace std;
Scheduler::Scheduler(int modeVal)
{
	timeStep = 1;
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
	mode = modeVal;

	processorIdx = 0;

	processorList = nullptr;
	SQF = nullptr;
	LQF = nullptr;
	tSQF = -1;
	tLQF = -1;

	//RNG SEED
	srand(time(nullptr));

	initializeUI(modeVal);
}

void Scheduler::initializeUI(int modeVal) {
	ui.set_mode(mode);
}

//Simple Simulator Fn.
void Scheduler::simulate() {
	fileLoading();
	while (TrmList.GetCount() != noProcesses) {
		NEWtoRDY();
		RDYtoRUN();
		RUNAlgo();
		BLKAlgo();
		//randKill();
		printTerminal();
		timeStep++;
	}
}

void Scheduler::fileLoading()
{
	ifstream Infile("input.txt");
	Infile >> NF >> NS >> NR;
	processorList = new Processor * [NF + NS + NR];// alocate processor pointers 
	Infile >> timeSlice;
	Infile >> RTF >> MaxW >> STL >> forkProb;
	Infile >> noProcesses;
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
	while (Infile >> sigkillTime >> killID)
	{
		sigPtr = new sigKill;
		sigPtr->tstep = sigkillTime;
		sigPtr->pID = killID;
		killQ.enqueue(sigPtr);
	}
}

//Step 1
void Scheduler::NEWtoRDY() {
	Process* p;
	bool canPeek = NewList.peek(p);
	while (canPeek && p->get_AT() == timeStep) {
		NewList.dequeue(p);
		processorList[processorIdx]->moveToRDY(p);
		processorIdx++;
		processorIdx = processorIdx % ProcessorsCounter;
		p = nullptr;
		//Recheck
		canPeek = NewList.peek(p);
	}
}

//Step 2
void Scheduler::RDYtoRUN() {
	for (int i = 0; i < ProcessorsCounter; i++) {
		processorList[i]->moveToRUN();
	}
}

//Step 3
void Scheduler::RUNAlgo() {
	for (int i = 0; i < ProcessorsCounter; i++) {
		processorList[i]->ScheduleAlgo();
	}
}

//Step 4
void Scheduler::BLKAlgo() {
	Process* p;
	bool canPeek = BlkList.peek(p);
	if (RNG() < 10 && canPeek) {
		BlkList.dequeue(p);
		processorList[processorIdx]->moveToRDY(p);
		processorIdx++;
		processorIdx = processorIdx % ProcessorsCounter;
		p = nullptr;
	}
}

//Step 5
void Scheduler::randKill() {
	for (int i = 0; i < ProcessorsCounter; i++) {
		processorList[i % NF]->ScheduleAlgo();
	}
}

int Scheduler::RNG() {
	return (rand() % 100 + 1);
}

//move to TRM fn
void Scheduler::schedToTRM(Process*& p)
{
	TrmList.enqueue(p);
}
//move to BLK fn
void Scheduler::schedToBLk(Process*& p)
{
	BlkList.enqueue(p);
}

//Print Terminal
void Scheduler::printTerminal() {
	ui.updateTerminal(timeStep, processorList, ProcessorsCounter, BlkList, TrmList);
}