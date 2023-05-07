#include "Process.h"

int Process::free_id = 0;

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
void Process::Load(ifstream& Infile)
{
	Infile >> AT >> PID >> CT >> N_IO;
	IO* ioData = new IO;
	for (int i = 0; i < N_IO; i++) {
		char c1, c2;
		Infile >> c1 >> ioData->IO_R >> c2 >> ioData->IO_D >> c1 >> c2;
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
int Process::get_count_fork() {
	//Currently a process can only fork once
	return rec_get_count_fork(lch) + rec_get_count_fork(rch);
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
	Process* p = nullptr;
	if (find(pid_parent, p)) {
		rec_mark_orphan(p->lch);
		rec_mark_orphan(p->rch);
	}
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
	//Assumes only one fork is done per lifetime
	parent = other.parent;
	if (parent) parent->lch = this;
	if (other.lch) {
		other.lch->parent = this;
		lch = other.lch;
	}
}


Process::~Process() {}