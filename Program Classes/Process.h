#pragma once
#include <iostream>
#include <fstream>
#include "../DEFS.h"
#include "../DS Implementations/LinkedQueue.h"
#include "../DS Implementations/PNode.h"
using namespace std;
class Process
{
private:
	//Process ID
	int PID;

	//Times
	int AT;		//Arrival time
	int RT;		//Response time
	int CT;		//CPU time
	int TT;		//Termination time
	int TRT;	//Turnaround duration
	int WT;		//Waiting time

	//Process State
	//state var has values: {0->5} which represent states: {NEW, RDY, RUN, BLK, TRM, ORPH}
	int state;

	//Input/Output Request time & Duration
	int N_IO;
	IO* ioData;//pointer placeholder for io data
	LinkedQueue<IO> ioQ;//Q contains all IOs the process will need

	//Kill Signal
	bool SIGKILL;

	//Fork Tree
	int count_forked;
	Process* lch;
	Process* rch;

	//Private setters: any data member that is calculated in terms of existing data members
	void set_TRT();
	void set_WT();

	//Count of forks
	void set_count(int val);

	//Assisting recursive functions
	void insertChHelper(Process*& subroot, Process* p);
	bool removeHelper(Process* subroot, int pid);
	void markOrphan(Process*& subroot);

public:
	Process(int at, int id, int ct, int STT, int ior, int iod); //Other data members are either calculate or recieved after creation
	Process();
	//Public setters
	void set_PID(int id);
	void set_AT(int at);
	void set_RT(int rt);
	void set_CT(int ct);
	void set_TT(int tt);
	void set_state(int STT);
	void set_IO(int ior, int iod);
	void set_SIGKILL(bool signal);

	//getters
	int get_PID();
	int get_AT();
	int get_RT();
	int get_CT();
	int get_TT();
	int get_TRT();
	int get_WT();
	int get_state();
	IO get_IO();
	bool get_SIGKILL();
	void Load(ifstream& Infile); // load its data mem from input file

	//Print ID
	friend ostream& operator<<(ostream& os, Process& p);

	//Fork Tree Methods
		//Tree getters
	Process*& get_lch();
	Process*& get_rch();
	int get_count();

		//Fork Tree operations
	void insertCh(Process*& p);
	bool remove(int pid);

	~Process();
};