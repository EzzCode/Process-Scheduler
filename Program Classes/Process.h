#pragma once
#include <iostream>
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
	int state;
	
	//Input/Output Request time & Duration
	int IO_R;
	int IO_D;
	
	//Kill Signal
	bool SIGKILL;

	//Private setters: any data member that is calculated in terms of existing data members
	void set_TRT();
	void set_WT();

public:
	Process(int at, int id, int ct, int ior, int iod); //Other data members are either calculate or recieved after creation

	//Public setters
	void set_PID(int id);
	void set_AT(int at);
	void set_RT(int rt);
	void set_CT(int ct);
	void set_TT(int tt);
	void set_state(int STT);
	void set_IO_R(int ior);
	void set_IO_D(int iod);
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
	int get_IO_R();
	int get_IO_D();
	bool get_SIGKILL();

	~Process();
};
