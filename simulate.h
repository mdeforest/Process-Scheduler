#ifndef SIMULATE_H
#define SIMULATE_H

#include "Scheduler.h"

double* simulate(Scheduler* sched, int numCPUBound, int numIOBound, int numCycles);

#endif
