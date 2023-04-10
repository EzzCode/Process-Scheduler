#include "Scheduler.h"

#include <fstream>

using namespace std;
Scheduler::Scheduler() 
{
	timeCounter = 0;
	ProcessorsCounter = 0;
}
void Scheduler::fileLoading()
{
	ifstream Infile("input.txt");
	Infile >> NF >> NS >> NR; 
	/*for (int i = 0; i < NF; i++) 
	{
		myProcessor = new FCFS(this);
		processorList[ProcessorsCounter] = myProcessor;
		ProcessorsCounter++;
	}*/
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
	Infile >> timeSlice;
	Infile >> RTF >> MaxW >> STL >> forkProb;
	Infile >> noProcesses;
	for (int i = 0; i < noProcesses; i++) 
	{
		myProcess = new Process;
		myProcess->Load(Infile);
		NewList.enqueue(myProcess);
	}
	// TO DO input SIGKILL times and IDS
}
//move to TRM fn
//move to BLK fn