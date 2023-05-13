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
	static int free_id;

	//Times
	int AT;		//Arrival time
	int RT;		//Response time
	int CT;		//CPU time
	int timer;	//Timer to calculate remaining CPU time
	int TT;		//Termination time
	int TRT;	//Turnaround duration
	int WT;		//Waiting time
	int DD;		//Expected Deadline

	//Process State
	//state var has values: {0->5} which represent states: {NEW, RDY, RUN, BLK, TRM, ORPH}
	int state;

	//Input/Output Request time & Duration
	int N_IO;
	LinkedQueue<IO> ioQ;	//Queue contains all IOs the process will need
	int total_IOD; //Total io duration of a process
	//Kill Signal
	bool SIGKILL;

	//Motion status
	bool has_moved;

	//Private setters for data members that are calculated in terms of existing data members
	void set_TRT();
	void set_WT();

	//Fork Tree variables
	Process* parent;
	Process* lch;
	Process* rch;

	//Private Tree Getters
	//DO I REALLY NEED THEM???
	Process* get_parent();
	Process* get_lch();
	Process* get_rch();

	//Assisting recursive functions
	int rec_get_count_fork(Process* subroot);
	bool rec_remove_subtree(Process* subroot, int pid);
	bool rec_find(Process* subroot, int pid, Process*& p);
	void rec_mark_orphan(Process* subroot);

public:
	Process(int at, int id, int ct, int stt); //Other data members are either calculated or recieved after creation
	Process();
	//Public setters
	void set_PID(int id);
	void set_AT(int at);
	void set_RT(int rt);
	void set_CT(int ct);
	void set_timer(int t);
	void set_TT(int tt);
	void set_DD(int dd);
	void set_state(int stt);
	void set_IO(int ior, int iod);
	void set_sig_kill(bool signal);
	void set_has_moved(bool motion);
	void set_total_IO(int tot);
	//getters
	int get_PID();
	int get_AT();
	int get_RT();
	int get_CT();
	int get_timer();
	int get_TT();
	int get_TRT();
	int get_WT();
	int get_DD();
	int get_state();
	bool peek_io(IO*& io);
	bool get_IO(IO*& io);
	bool get_sig_kill();
	bool get_has_moved();
	int get_total_IO();
	void Load(ifstream& Infile); // load its data members from input file

	//Print ID
	friend ostream& operator<<(ostream& os, Process& p);
	// Write in output File
	void writeData(ofstream& OutFile);
	/*Fork Tree Methods
	Fork Tree is used to keep track of ancestors & descendants and update them if needed*/
	//Fork Tree operations
	int get_count_fork();
	bool insert_ch(Process* p);
	bool remove_subtree(int pid);
	bool find(int pid, Process*& p);
	void mark_orphan(int pid_parent);
	bool has_parent();
	bool has_single_ch();
	bool has_both_ch();

	//cpy ctor
	Process(const Process& other);

	~Process();
};