//Definitions for custom types
#ifndef DEFS_H
#define DEFS_H
struct IO {
	int IO_D;
	int IO_R;
	IO() :IO_D(0), IO_R(0) {}
	IO(int d, int r) : IO_D(d), IO_R(r) {}
	IO(const IO& other) : IO_D(other.IO_D), IO_R(other.IO_R) {}
};
struct sigKill {
	int tstep;
	int pID;
};
#endif