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
	//Keep track of IDs
	static int last_id;

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
	IO* ioData;				//pointer placeholder for io data
	LinkedQueue<IO> ioQ;	//Queue contains all IOs the process will need

	//Kill Signal
	bool SIGKILL;

	//Fork Tree
	Process* lch;
	Process* rch;

	//Private setters for data members that are calculated in terms of existing data members
	void set_TRT();
	void set_WT();

	//Assisting recursive functions
	void rec_insert_ch(Process* subroot, Process* p);
	bool rec_remove(Process* subroot, int pid);
	bool rec_search(Process* subroot, int pid, Process*& p);
	void rec_mark_orphan(Process* subroot);
	int rec_get_count_fork(Process* subroot);
	void cpyTree(const Process& p);


public:
	Process(int at, int id, int ct, int stt); //Other data members are either calculated or recieved after creation
	Process();
	//Public setters
	void set_PID(int id);
	static void set_last_id(int value);
	static int get_last_id();
	void set_AT(int at);
	void set_RT(int rt);
	void set_CT(int ct);
	void set_TT(int tt);
	void set_state(int stt);
	void set_IO(int ior, int iod);
	void set_sig_kill(bool signal);

	//getters
	int get_PID();
	int get_AT();
	int get_RT();
	int get_CT();
	int get_TT();
	int get_TRT();
	int get_WT();
	int get_state();
	bool get_IO(IO*& io);
	bool get_sig_kill();
	void Load(ifstream& Infile); // load its data members from input file

	//Print ID
	friend ostream& operator<<(ostream& os, Process& p);

	//Fork Tree Methods
		//Tree getters
	bool get_lch(Process*& p);
	bool get_rch(Process*& p);
	int get_count_fork();

	//Fork Tree operations
	void insert_ch(Process* p);
	bool remove(int pid);
	bool search(int pid, Process*& p);
	void mark_orphan(int pid_parent);

	//cpy ctor
	Process(const Process& other);

	~Process();
};