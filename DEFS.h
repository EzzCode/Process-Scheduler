//Definitions for custom types
#ifndef DEFS_H
#define DEFS_H
struct IO {
	int IO_R;
	int IO_D;
	IO() :IO_D(0), IO_R(0) {}
	IO(int r, int d) : IO_D(d), IO_R(r) {}
	IO(const IO& other) : IO_D(other.IO_D), IO_R(other.IO_R) {}
};
struct sigKill {
	int tstep;
	int pID;
	sigKill() : tstep(0), pID(0) {}
	sigKill(int t, int id) : tstep(t), pID(id) {}
	sigKill(const sigKill& other) : tstep(other.tstep), pID(other.pID) {}
};
#endif