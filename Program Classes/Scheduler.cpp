#include "Scheduler.h"

#include <fstream>

using namespace std;
Scheduler::Scheduler() 
{
	timeCounter = 0;
	noProcessors = 0;
}
void Scheduler::fileLoading()
{
	ifstream Infile("input.txt");
	Infile >> NF >> NS >> NR; 
	for (int i = 0; i < NF; i++) 
	{
		myProcessor = new FCFS;
		processorList[noProcessors] = myProcessor;
		noProcessors++;
	}
	for (int i = 0; i < NS; i++)
	{
		myProcessor = new SJF;
		processorList[noProcessors] = myProcessor;
		noProcessors++;
	}
	for (int i = 0; i < NR; i++)
	{
		myProcessor = new RR;
		processorList[noProcessors] = myProcessor;
		noProcessors++;
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