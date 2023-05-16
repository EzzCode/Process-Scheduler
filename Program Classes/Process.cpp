#include "Process.h"
#include <iostream>
#include <iomanip>
using namespace std;
int Process::free_id = 1;

Process::Process(int at, int id, int ct, int stt) {
	set_PID(id);
	set_AT(at);
	set_CT(ct);
	set_timer(ct);
	set_state(stt);
	set_RT(-1);		//-1 indicates that process has never entered CPU
	set_sig_kill(false);
	//Fork Tree
	parent = nullptr;
	lch = nullptr;
	rch = nullptr;

	total_IOD;
}
Process::Process() {
	set_RT(-1);		//-1 indicates that process has never entered CPU
	set_sig_kill(false);
	//Fork Tree
	parent = nullptr;
	lch = nullptr;
	rch = nullptr;
}
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
void Process::set_timer(int t)
{
	timer = t;
}
void Process::set_TT(int tt) {
	TT = tt;
	set_TRT();
	set_WT();
}
void Process::set_DD(int dd)
{
	DD = dd;
}
void Process::set_TRT() {
	TRT = get_TT() - get_AT();
}
void Process::set_WT() {
	WT = get_TRT() - get_CT();
}
void Process::set_state(int stt) {
	state = stt;
}
void Process::set_IO(int ior, int iod) {
	IO* ioData = new IO(iod, ior);
	ioQ.enqueue(ioData);
}
void Process::set_total_IO(int tot)
{
	total_IOD = tot;
}

void Process::set_sig_kill(bool signal) {
	SIGKILL = signal;
}

void Process::set_has_moved(bool motion)
{
	has_moved = motion;
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
int Process::get_timer()
{
	return timer;
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
int Process::get_DD()
{
	return DD;
}
int Process::get_state() {
	return state;
}
bool Process::peek_io(IO*& io) {
	return ioQ.peek(io);
}
bool Process::get_IO(IO*& io) {
	return ioQ.dequeue(io);
	
}
bool Process::get_sig_kill() {
	return SIGKILL;
}
bool Process::get_has_moved()
{
	return has_moved;
}
int Process::get_total_IO()
{
	return total_IOD;
}
void Process::Load(ifstream& Infile)
{
	Infile >> AT >> PID >> CT >> DD >> N_IO;
	IO* ioData = new IO;
	int tR = 0;
	for (int i = 0; i < N_IO; i++) {
		char c1, c2;
		int x;
		Infile >> c1 >> x >> c2 >> ioData->IO_D >> c1 >> c2;
		ioData->IO_R = x - tR;
		tR = x;
		ioQ.enqueue(ioData);
		if (i != N_IO - 1) {
			ioData = new IO;
		}
	}
	free_id++;
	set_timer(CT);
	set_RT(-1);
	set_state(0);
	set_sig_kill(false);
	//Fork Tree
	parent = nullptr;
	lch = nullptr;
	rch = nullptr;
}

//Print ID
ostream& operator<<(ostream& os, Process& p) {
	return os << p.get_PID();
}

//Fork Tree Methods
//Private Tree getters
Process* Process::get_parent()
{
	return parent;
}

Process* Process::get_lch() {
	return lch;
}

Process* Process::get_rch() {
	return rch;
}

//Fork tree operations
int Process::get_count_ch() {
	if (lch && rch) return 2;
	else if (lch || rch) return 1;
	else return 0;
}

int Process::count_direct_orph()
{
	int count = 0;
	if (lch && lch->get_state() != 4) count++;
	if (rch && rch->get_state() != 4)count++;
	return count;
}

bool Process::insert_ch(Process* p) {
	if (!this->lch) {
		this->lch = p;
		p->parent = this;
		p->set_PID(free_id);
		free_id++;
		return true;
	}
	else if (!this->rch) {
		this->rch = p;
		p->parent = this;
		p->set_PID(free_id);
		free_id++;
		return true;
	}
	return false;
}

bool Process::remove_subtree(int pid) {
	bool removed = rec_remove_subtree(this, pid);
	return removed;
}

bool Process::find(int pid, Process*& p)
{
	return rec_find(this, pid, p);
}

void Process::mark_orphan(int pid_parent)
{
	if (lch && lch->state != 4) lch->set_state(5);
	if (rch && rch->state != 4) rch->set_state(5);
}

bool Process::has_parent()
{
	return (parent != nullptr);
}

bool Process::has_single_ch()
{
	return (lch != nullptr || rch != nullptr);
}

bool Process::has_both_ch()
{
	return (lch != nullptr && rch != nullptr);
}

//Fork tree assisting recursive functions
int Process::rec_get_count_fork(Process* subroot)
{
	if (!subroot || subroot->get_state() == 4 || subroot->get_state() == 5) return 0; //Check if NULL / TRM / ORPH
	return 1 + rec_get_count_fork(subroot->lch) + rec_get_count_fork(subroot->rch);
}

bool Process::rec_remove_subtree(Process* subroot, int pid) {
	if (!subroot) return false;
	int id = subroot->get_PID();
	if (id == pid) {
		rec_mark_orphan(subroot->lch);
		rec_mark_orphan(subroot->rch);
		return true;
	}
	return rec_remove_subtree(subroot->lch, pid) || rec_remove_subtree(subroot->rch, pid);
}
bool Process::rec_find(Process* subroot, int pid, Process*& p)
{
	if (!subroot) {
		return false;
	}
	if (subroot->PID == pid) {
		p = subroot;
		return true;
	}
	if (rec_find(subroot->lch, pid, p)) return true;
	return rec_find(subroot->rch, pid, p);
}
void Process::rec_mark_orphan(Process* subroot) {
	if (!subroot) return;
	subroot->set_state(5);
	rec_mark_orphan(subroot->lch);
	rec_mark_orphan(subroot->rch);
}
//Write in output file 
void Process::writeData(ofstream& OutFile)
{
	OutFile << TT << "   " << PID << "    " << AT << "   " << CT << "    " << total_IOD << "   " << WT << "   " << RT <<"   " << TRT << endl;
}

//copy ctor
Process::Process(const Process& other) {
	//cpy ID
	PID = other.PID;
	//cpy times
	AT = other.AT;
	RT = other.RT;
	CT = other.CT;
	timer = other.timer;
	TT = other.TT;
	TRT = other.TRT;
	WT = other.WT;
	DD = other.DD;
	//cpy process state
	state = other.state;
	//cpy IO data
	N_IO = other.N_IO;
	ioQ = LinkedQueue<IO>(other.ioQ);
	//cpy kill signal
	SIGKILL = other.SIGKILL;
	//Motion status
	has_moved = other.has_moved;
	//cpy Fork Tree
	parent = other.parent;
	if (parent)	// if this process has a parent
	{
		// check if this process is lch or rch
		if (parent->lch)
		{
			if (parent->lch->get_PID() == PID) parent->lch = this;
		}
		if(parent->rch)
		{
			if (parent->rch->get_PID() == PID) parent->rch = this;
		}
	}
	// check if this process has lch and/or rch
	if (other.lch) {
		other.lch->parent = this;
		lch = other.lch;
	}
	if (other.rch) {
		other.rch->parent = this;
		rch = other.rch;
	}
	total_IOD = other.total_IOD;
}



Process::~Process() {}

