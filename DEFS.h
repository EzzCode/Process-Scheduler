//Definitions for custom types
#ifndef DEFS_H
#define DEFS_H
struct IO {
    int IO_D;
    int IO_R;
};
struct sigKill {
    int tstep;
    int pID;
};
enum processStates {
    NEW,
    RDY,
    RUN,
    BLK,
    TRM,
    ORPH
};
enum processorStates
{
    BUSY,
    IDLE
};
#endif
