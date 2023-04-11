#include "Process.h"

Process::Process(int at, int id, int ct, int STT, int ior, int iod) {
	set_PID(id);
	set_AT(at);
	set_CT(ct);
	set_state(STT);
	set_IO(ior, iod);
	set_RT(-1);		//-1 indicates that process has never entered CPU
	set_SIGKILL(false);
}
Process::Process() {}
//setters
void Process::set_PID(int id) {
	PID = id;
}
void Process::set_AT(int at) {
	AT = at;
}
void Process::set_RT(int rt) {
	RT = rt;
}
void Process::set_CT(int ct) {
	CT = ct;
}
void Process::set_TT(int tt) {
	TT = tt;
	set_TRT();
	set_WT();
}
void Process::set_TRT() {
	TRT = get_TT() - get_AT();
}
void Process::set_WT() {
	WT = get_TRT() - get_CT();
}
void Process::set_state(int STT) {
	state = STT;
}
void Process::set_IO(int ior, int iod) {
	ioData.IO_D = iod;
	ioData.IO_R = ior;
}
void Process::set_SIGKILL(bool signal) {
	SIGKILL = signal;
}

//getters
int Process::get_PID() {
	return PID;
}
int Process::get_AT() {
	return AT;
}
int Process::get_RT() {
	return RT;
}
int Process::get_CT() {
	return CT;
}
int Process::get_TT() {
	return TT;
}
int Process::get_TRT() {
	return TRT;
}
int Process::get_WT() {
	return WT;
}
int Process::get_state() {
	return state;
}
IO Process::get_IO() {
	return ioData;
}
bool Process::get_SIGKILL() {
	return SIGKILL;
}
void Process::Load(ifstream& Infile)
{
	Infile >> AT >> PID >> CT >> N_IO;
	for (int i = 0; i < N_IO; i++) {
		char c1, c2;
		//Infile >> c1 >> IO_R >> c2 >> IO_D >> c1 >> c2;
	}
}
//Print ID
ostream& operator<<(ostream& os, Process& p) {
	return os << p.get_PID();
}

Process::~Process() {}