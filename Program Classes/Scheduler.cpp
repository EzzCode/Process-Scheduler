#include "Scheduler.h"

#include <fstream>

using namespace std;
Scheduler::Scheduler()
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
	initializeUI();
}

void Scheduler::initializeUI() {
	ui.request_mode();	// gets mode of operation from user
}

//Simulator Fn.
void Scheduler::simulate() {
	ui.silent_print();
	fileLoading();
	while (TrmList.GetCount() != noProcesses) {
		NEWtoRDY();
		RDYtoRUN();
		RUNAlgo();
		BLKAlgo();
		Kill();
		Steal();
		OVHT();
		printTerminal();
		timeStep++;
	}
	//remove overheat from any prcsr
	for (int i = 0; i < ProcessorsCounter; i++)
	{
		processorList[i]->set_overheat(false);
	}
	//print output file
	outputFile();
	// End Sim
	ui.print_end();
}

void Scheduler::fileLoading()
{
	ifstream Infile("input.txt");
	Infile >> NF >> NS >> NR >> NE;
	processorList = new Processor * [NF + NS + NR + NE];	// allocate processor pointers
	Infile >> timeSlice;
	Infile >> RTF >> MaxW >> STL >> forkProb >> ovht_tSteps;
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
		//Find shortest prcsr
		set_SQF_LQF(0, true);	// must return a value, can't delay to next timestep
		NewList.dequeue(p);
		SQF->moveToRDY(p);
		p = nullptr;
		//Recheck
		canPeek = NewList.peek(p);
	}
}

//RDY to RUN
void Scheduler::RDYtoRUN() {
	for (int i = 0; i < ProcessorsCounter; i++) {
		if (processorList[i]->is_overheated()) continue;	// prcsr overheated
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
	set_SQF_LQF(processor);
	if (!SQF) return false;	// prcsrs of this type are overheated
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
		if (processorList[i]->is_overheated()) continue;	// prcsr overheated
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
			//Find shortest prcsr
			set_SQF_LQF(0);
			if (!SQF) return;	// all prcsrs overheated
			BlkList.dequeue(p);
			p->get_IO(io);
			SQF->moveToRDY(p);
			SQF->moveToRUN();
			p = nullptr;
			delete io;
			io = NULL;
		}
		else {
			p->set_total_IO((p->get_total_IO()) + 1);//increments the total io Duration for the output file
			io->IO_D--;
		}
	}
}

//SIGKILL
void Scheduler::Kill() {
	killQ.peek(sigPtr);
	bool killed = false;
	bool getOut = false;
	while (sigPtr->tstep == timeStep)
	{
		killQ.dequeue(sigPtr);
		for (int i = 0; i < NF; i++) {
			if (processorList[i]->is_overheated()) continue;	// prcsr overheated
			//fn returns true if killed
			killed = processorList[i]->RDYKill(sigPtr->pID);
			if (killed)
			{
				KillCount++;
				killed = false;
			}
			else if(!killed && i==NF-1)
			{
				getOut = true;
			}
		}
		if(getOut==false)
		{
			killQ.peek(sigPtr);
		}
		else 
		{
			killQ.dequeue(sigPtr);
			break;
		}
		
	}

}

void Scheduler::Steal()
{
	if (timeStep % STL == 0)
	{
		while (getSTL_limit() > 0.4)
		{
			set_SQF_LQF(0);
			if (!SQF || !LQF) return;	// all prcsrs overheated
			// can't steal if the difference is caused by one or less processes only
			if (LQF->get_rdy_count() - SQF->get_rdy_count() <= 1) break;
			// else can steal
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
		KillCount += p->count_direct_orph();
		kill_orph(p);	// recursively killing orphans; from leaf to root
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
	set_SQF_LQF(1);	//Get shortest FCFS queue to process child
	if (!SQF) return;	// all FCFS prcsrs overheated
	Process* ch = new Process(timeStep, -1, parent->get_timer(), 0);
	parent->insert_ch(ch);
	noProcesses++;	//Update variable for scheduler
	SQF->moveToRDY(ch);
}

// kill forked orphans
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

// Processor overheat manager
void Scheduler::OVHT()
{
	int ovht_prob = 1; // overheat percentage is constant and equals 1%
	// each processor is checked for one of 2 conditions
	// 1st: prcsr is overheated and we decrement time steps of overheat until end of overheat
	// 2nd: prcsr is NOT overheated and we check possibility of overheat
	for (int i = 0; i < ProcessorsCounter; i++)
	{
		Processor* prcsr = processorList[i];
		// 1st cond: is overheated
		if (prcsr->is_overheated())
		{
			if (prcsr->get_rem_ovht_steps() > 0) prcsr->decrement_ovht_steps();
			else prcsr->set_overheat(false);	// processor finished overheating
			continue;
		}
		// 2nd cond: is NOT overheated
		int rng = RNG();
		if (rng > ovht_prob) continue;	// no overheat
		// else overheats
		prcsr->set_overheat(true, ovht_tSteps);

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
void Scheduler::set_SQF_LQF(int section, bool forced)
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

	SQF = nullptr; LQF = nullptr;

	//if forced is true then it doesn't matter if processor is overheated
	for (int i = start; i < end; i++)
	{
		if (processorList[i]->getQueueLength() > max && (forced || !processorList[i]->is_overheated()))
		{
			LQF = processorList[i];
			max = processorList[i]->getQueueLength();
		}
		if (processorList[i]->getQueueLength() < min && (forced || !processorList[i]->is_overheated()))
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

void Scheduler::calc_RT(Process* p)
{
	p->set_RT(timeStep - p->get_AT());
}

bool Scheduler::clear_ovht_prcsr(Process* p)
{
	if (p->has_parent())	// check if forked process
	{
		// child process must remain in an FCFS prcsr
		set_SQF_LQF(1);
		if (SQF)	// check if there is another FCFS prcsr
		{
			SQF->moveToRDY(p);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		set_SQF_LQF(0);
		if (SQF)	// check if there are other prcsrs
		{
			SQF->moveToRDY(p);
			return true;
		}
		else
		{
			return false;
		}
	}
}

void Scheduler::BeforeDDManager(Process* pPtr)
{
	if (pPtr->get_DD() > timeStep)
	{
		BeforeDD++;
	}
}

//STATISTICS 
void Scheduler::setStats(Process* p)
{
	AvgTRT += p->get_TRT();
	AvgRT += p->get_RT();
	AvgWT += p->get_WT();
	ForkCount += p->get_count_ch();
}

int Scheduler::getTimeSlice()
{
	return timeSlice;
}

int Scheduler::getRTF()
{
	return RTF;
}

int Scheduler::getMaxW()
{
	return MaxW;
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
		//dealloc
		p->sever_connections();
		delete p;
		p = nullptr;
	}

	OutFile << "Processes: " << noProcesses << endl;
	OutFile << "Avg WT: " << getAvgWT() << ",  " << "Avg RT: " << getAvgRT() << ", " << "Avg TRT: " << getAvgTRT() << endl;
	OutFile << "Migration %: " << "RTF:" << getRTFpercent() * 100 << "% " << "MaxW: " << getMaxWpercent() * 100 << "%" << endl;
	OutFile << "Work Steal % : " << getSTLpercent() * 100 << "%" << endl;
	OutFile << "Forked Process % : " << getForkedpercent() * 100 << "%" << endl;
	OutFile << "Killed process % : " << getKillpercent() * 100 << "%" << endl;
	OutFile << endl;
	OutFile << "Processors: " << ProcessorsCounter << " " << "[" << NF << " " << "FCFS, " << NS << " " << "SJF, " << NR << " " << "RR, " << NE << "EDF" << "]" << endl;
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
	OutFile << "Processors Util" << endl;
	for (int i = 0; i < ProcessorsCounter; i++)
	{



		OutFile << "P" << i + 1 << "=" << processorList[i]->getpUtil() * 100 << "%" << ", ";
		avgUtil += processorList[i]->getpUtil() * 100;


	}
	OutFile << endl;
	OutFile << "Avg Util: " << avgUtil / ProcessorsCounter << "%" << endl;
	OutFile << "Percentage of processes completed before their expected deadline: " << getBeforeDDpercent() * 100 << "%" << endl;

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