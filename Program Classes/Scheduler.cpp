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

	processorList = nullptr;
	SQF = nullptr;
	LQF = nullptr;
	tSQF = -1;
	tLQF = -1;
	//Statistics
	KillCount = 0;
	ForkCount = 0;
	STLCount = 0;
	RTF_migCount = 0;
	MaxW_migCount = 0;
	BeforeDD = 0;
	avgUtil = 0;
	//RNG SEED
	srand(time(nullptr));

	//UI initialization
	initializeUI(modeVal);
}

void Scheduler::initializeUI(int modeVal) {
	ui.set_mode(mode);
}

//Simulator Fn.
void Scheduler::simulate() {
	fileLoading();
	while (TrmList.GetCount() != noProcesses) {
		NEWtoRDY();
		RDYtoRUN();
		RUNAlgo();
		BLKAlgo();
		Kill();
		Steal();
		printTerminal();
		timeStep++;
	}
	
	outputFile();
	ui.print_end();
}

void Scheduler::fileLoading()
{
	ifstream Infile("input.txt");
	Infile >> NF >> NS >> NR >> NE;
	processorList = new Processor * [NF + NS + NR + NE];// alocate processor pointers 
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
	for (int i = 0; i < NE; i++)
	{
		myProcessor = new EDF(this);
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

//NEW to RDY
void Scheduler::NEWtoRDY() {
	Process* p = nullptr;
	bool canPeek = NewList.peek(p);
	while (canPeek && p->get_AT() == timeStep) {
		NewList.dequeue(p);
		//Find shortest prcsr
		set_SQF_LQF(0);
		SQF->moveToRDY(p);
		p = nullptr;
		//Recheck
		canPeek = NewList.peek(p);
	}
}

//RDY to RUN
void Scheduler::RDYtoRUN() {
	for (int i = 0; i < ProcessorsCounter; i++) {
		processorList[i]->moveToRUN();
	}
}

void Scheduler::Migrate(Process* pPtr, int processor)
{
	set_SQF_LQF(processor); //3 for RR -- 2 for SJF 
	SQF->moveToRDY(pPtr);
	if (processor == 3) MaxW_migCount++; //Count for FCFS migration
	else if (processor == 2) RTF_migCount++; //Count for RR migration
}

bool Scheduler::canMigrate(Process* pPtr, int processor)
{
	if (pPtr->has_parent())
		return false;
	switch (processor)
	{
		case 3:
		{
			if ((timeStep - pPtr->get_AT() - pPtr->get_CT() + pPtr->get_timer()) > MaxW)
			{
				return true;
			}
			return false;
		}
		case 2:
		{
			if (pPtr->get_timer() < RTF)
			{
				return true;
			}
			return false;
		}
		default:
			return false;
	}
}

//RUN Algorithm
void Scheduler::RUNAlgo() {
	for (int i = 0; i < ProcessorsCounter; i++) {
		processorList[i]->ScheduleAlgo();
	}
}

//BLK Algorithm
void Scheduler::BLKAlgo() {
	Process* p = nullptr;
	IO* io = nullptr;
	bool canPeek = BlkList.peek(p);
	if (canPeek)
	{
		bool b = p->peek_io(io);//Get IO ptr
		if (b && io->IO_D == 0)
		{
			BlkList.dequeue(p);
			p->get_IO(io);
			//Find shortest prcsr
			set_SQF_LQF(0);
			SQF->moveToRDY(p);
			p = nullptr;
			delete io;
			io = NULL;
		}
		else {
			p->set_total_IO((p->get_total_IO())+1);//increments the total io Duration for the output file
			io->IO_D--;
		}
	}
}

//Random Kill
void Scheduler::Kill() {
	killQ.peek(sigPtr);
	if (sigPtr->tstep == timeStep)
	{
		killQ.dequeue(sigPtr);
		KillCount++;
		for (int i = 0; i < NF; i++) {
			processorList[i]->RDYKill(sigPtr->pID);
		}
	}

}

void Scheduler::Steal()
{
	if (timeStep % STL == 0)
	{
		while (getSTL_limit() > 0.4 && (TrmList.GetCount() + BlkList.GetCount()) - noProcesses > 1)
		{
			set_SQF_LQF(0);
			Process* s = LQF->steal();
			if (!s)
			{
				return;
			}
			SQF->moveToRDY(s);
			STLCount++;
		}
	}
}



int Scheduler::RNG() {
	return (rand() % 100 + 1);
}

//Move to TRM list
void Scheduler::schedToTRM(Process* p)
{
	//Check and kill process orphans
	if (p->has_single_ch())
	{
		kill_orph(p);
	}
	p->set_TT(timeStep);
	TrmList.enqueue(p);
}
//Move to BLK list
void Scheduler::schedToBLk(Process* p)
{
	BlkList.enqueue(p);
}

//Forking
void Scheduler::fork(Process* parent) {
	//check probability
	int rng = RNG();
	if (rng > forkProb || parent->has_both_ch()) return;	//Can't fork
	//Can Fork
	Process* ch = new Process(timeStep, -1, parent->get_timer(), 0);
	parent->insert_ch(ch);
	noProcesses++;	//Update variable for scheduler
	set_SQF_LQF(1);	//Get shortest FCFS queue to process child
	SQF->moveToRDY(ch);
}

void Scheduler::kill_orph(Process* parent)
{
	// mark orphans of parent
	parent->mark_orphan(parent->get_PID());
	// loop on FCFS processors and kill found orphans
	for (int i = 0; i < NF; i++)
	{
		processorList[i]->kill_orph();
	}
}

//Print Terminal
void Scheduler::printTerminal() {
	ui.updateTerminal(timeStep, processorList, ProcessorsCounter, BlkList, TrmList);
}

//Calculate Steal Limit
float Scheduler::getSTL_limit()
{
	set_SQF_LQF(0);
	return (tLQF - tSQF) / ((float)tLQF);
}

//Set Shortest Queue and Longest Queue (Time & Processor)
void Scheduler::set_SQF_LQF(int section)
{
	int max = INT_MIN;
	int min = INT_MAX;
	//Variables to set loop paremeters
	int start, end;
	//Set Paremeters
	switch (section)
	{
	case 0: //full loop
		start = 0;
		end = ProcessorsCounter;
		break;
	case 1: //FCFS
		start = 0;
		end = NF;
		break;
	case 2: //SJF
		start = NF;
		end = NF + NS;
		break;
	case 3: //RR
		start = NF + NS;
		end = NF + NS + NR;
		break;
	case 4: //EDF
		start = NF + NS + NR;
		end = ProcessorsCounter;
	default: //full loop
		start = 0;
		end = ProcessorsCounter;
		break;
	}

	for (int i = start; i < end; i++)
	{
		if (processorList[i]->getQueueLength() > max)
		{
			LQF = processorList[i];
			max = processorList[i]->getQueueLength();
		}
		if (processorList[i]->getQueueLength() < min)
		{
			SQF = processorList[i];
			min = processorList[i]->getQueueLength();
		}
	}
	tLQF = max;
	tSQF = min;
}
int Scheduler::getSQF_time(int section)
{
	set_SQF_LQF(section);
	return tSQF;
}
int Scheduler::getLQF_time(int section)
{
	set_SQF_LQF(section);
	return tLQF;
}

//STATISTICS 
void Scheduler::setStats(Process* p)
{
	AvgTRT += p->get_TRT();
	AvgRT += p->get_RT();
	AvgWT += p->get_WT();
	ForkCount += p->get_count_fork();
	
}

int Scheduler::getTimeSlice()
{
	return timeSlice;
}

int Scheduler::getRTF()
{
	return RTF;
}

void Scheduler::calc_RT(Process* p)
{
	p->set_RT(timeStep - p->get_AT());
}

int Scheduler::getMaxW()
{
	return MaxW;
}

void Scheduler::BeforeDDManager(Process* pPtr)
{
	if (pPtr->get_DD() > timeStep)
	{
		BeforeDD++;
	}
}

float Scheduler::getAvgWT()
{
	return (float)AvgWT / noProcesses;;
}

float Scheduler::getAvgRT()
{
	return (float)AvgRT / noProcesses;
}

float Scheduler::getAvgTRT()
{
	return (float)AvgTRT / noProcesses;
}

float Scheduler::getBeforeDDpercent()
{
	return (float)BeforeDD / noProcesses;
}

int Scheduler::getTotalTRTALL()
{
	return total_TRT_ALL;
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
//Output File
void Scheduler::outputFile()
{
	Process* p;
	ofstream OutFile("Output.txt");
	OutFile << "TT  PID  AT  CT  IO_D  WT  RT  TRT" << endl;
	while (!TrmList.isEmpty())
	{
		TrmList.peek(p);
		p->writeData(OutFile);
		setStats(p);
		TrmList.dequeue(p);
	}

	OutFile << "Processes: " << noProcesses << endl;
	OutFile << "Avg WT: " << getAvgWT() << ",  " << "Avg RT: " << getAvgRT() << ", " << "Avg TRT: " << getAvgTRT() << endl;
	OutFile << "Migration %: " << "RTF:" << getRTFpercent() * 100 << "% " << "MaxW: " << getMaxWpercent() * 100 << "%" << endl;
	OutFile << "Work Steal % : " << getSTLpercent() * 100 << endl;
	OutFile << "Forked Process " << getForkedpercent() * 100 << "%" << endl;
	OutFile << "Killed process " << getKillpercent() * 100 << "%" << endl;
	OutFile << endl;
	OutFile << "Processors: " << ProcessorsCounter << " " << "[" << NF << " " << "FCFS, " << NS << " " << "SJF, " << NR << " " << "RR, " <<NE<<"EDF" <<"]" << endl;
	OutFile << "Processors Load" << endl;
	for (int i = 0; i < ProcessorsCounter; i++) 
	{
		total_TRT_ALL += processorList[i]->getTotalTRT();
	}
	for (int i = 0; i < ProcessorsCounter; i++)
	{
		if (i >= NF + NS && i <= NF + NS + NR - 1)
		{
			OutFile << "P" << i + 1 << "=" << "N/A" << ", ";
		}
		else 
		{
			processorList[i]->setTotalTRT(total_TRT_ALL);
			OutFile << "P" << i + 1 << "=" << processorList[i]->getpLoad() * 100 << "%" << ", ";
		}
		
	}
	OutFile << endl;
	OutFile<< "Processors Util" << endl;
	for (int i = 0; i < ProcessorsCounter; i++)
	{

		
		
			OutFile << "P" << i + 1 << "=" << processorList[i]->getpUtil() * 100 << "%" << ", ";
			avgUtil += processorList[i]->getpUtil() * 100;
		
		
	}
	OutFile << endl;
	OutFile << "Avg Util: " << avgUtil / ProcessorsCounter <<"%" << endl;
	OutFile << "Percentage of processes completed before tehir expected deadline: " << getBeforeDDpercent() * 100 <<"%" << endl;

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