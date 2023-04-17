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
		randKill();
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
	//processor creation
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
		int RT = p->get_AT() - timeStep;
		p->set_RT(RT);
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
	Process* p = nullptr;
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
	int pID = rand() % noProcesses + 1;
	for (int i = 0; i < NF; i++) {
		processorList[i]->RDYKill(pID);
	}
}

int Scheduler::RNG() {
	return (rand() % 100 + 1);
}

//move to TRM fn
void Scheduler::schedToTRM(Process* p)
{
	p->set_TT(timeStep);
	TrmList.enqueue(p);
}
//move to BLK fn
void Scheduler::schedToBLk(Process* p)
{
	BlkList.enqueue(p);
}

//Print Terminal
void Scheduler::printTerminal() {
	ui.updateTerminal(timeStep, processorList, ProcessorsCounter, BlkList, TrmList);
}

//Calculate Steal Limit
float Scheduler::getSTL_limit()
{
	return (tLQF - tSQF) / ((float)tLQF);
}

//Set Shortest Queue and Longest Queue (Time & Processor)
void Scheduler::set_SQF_LQF()
{
	int max = INT_MIN;
	int min = INT_MAX;

	for (int i = 0; i < ProcessorsCounter; i++)
	{
		if (processorList[i]->getQueueLength() > max)
		{
			LQF = processorList[i];
			max = processorList[i]->getQueueLength();
		}
		else if (processorList[i]->getQueueLength() < min)
		{
			SQF = processorList[i];
			min = processorList[i]->getQueueLength();
		}
	}
	tLQF = max;
	tSQF = min;
}
int Scheduler::getSQF_time()
{
	set_SQF_LQF();
	return tSQF;
}
int Scheduler::getLQF_time()
{
	set_SQF_LQF();
	return tLQF;
}

//STATISTICS 
void Scheduler::setStats()
{
	Process* p;
	while (TrmList.dequeue(p))
	{
		AvgTRT += p->get_TRT();
		AvgRT += p->get_RT();
		AvgWT += p->get_WT();
		ForkCount += p->get_count_fork();
	}
	AvgTRT = (float)AvgTRT / noProcesses;
	AvgRT = (float)AvgRT / noProcesses;
	AvgWT = (float)AvgWT / noProcesses;
}

float Scheduler::getAvgWT()
{
	return AvgWT;
}

float Scheduler::getAvgRT()
{
	return AvgRT;
}

float Scheduler::getAvgTRT()
{
	return AvgTRT;
}

float Scheduler::getRTFpercent()
{
	return (float)RTF_migCount / noProcesses;
}

float Scheduler::getMaxWpercent()
{
	return (float)MaxW_migCount / noProcesses;
}

float Scheduler::getForkedpercent()
{
	return (float)ForkCount / noProcesses;
}

float Scheduler::getKillpercent()
{
	return (float)KillCount / noProcesses;
}

float Scheduler::getSTLpercent()
{
	return (float)STLCount / noProcesses;
}

//Destructor
Scheduler::~Scheduler()
{
	for (int i = 0; i < NF + NS + NR; i++) {
		delete processorList[i];
	}
	// Free memory for processorList
	delete[] processorList;
}