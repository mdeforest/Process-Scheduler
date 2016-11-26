//simulate.cc

#include <chrono>
#include <iostream>
#include <queue>

#include "simulate.h"
#include "Scheduler.h"

using namespace std;

double* simulate(Scheduler* sched, int numCPUBound, int numIOBound, int numCycles)
{
  /*Simulate the CPU scheduler with the specified number of CPU-bound and
    I/O-bound processes; return an array containing some important statistics*/

  queue<Process*> newQueue;

  for (int i = 0; i < numCPUBound; i++) { //add CPU-bound processes to scheduler
    double idNumber = i + 1;
    CPUBoundProcess* proc = new CPUBoundProcess(idNumber);
    sched -> addProcess(proc);
    newQueue.push(proc);
  } 

  for (int i = 0; i < numIOBound; i++) { //add IO-bound processes to scheduler
    double idNumber = -(i+1);
    IOBoundProcess* proc = new IOBoundProcess(idNumber);
    sched -> addProcess(proc);
    newQueue.push(proc);
  }

  double simCycles = 0;

  double CPUTime = 0;
  double CPUWait = 0;

  double IOTime = 0;
  double IOWait = 0;
  
  auto t1 = chrono::system_clock::now();
  while (simCycles <= numCycles) {
    Process* nextProc = sched -> popNext(simCycles);
    simCycles += nextProc -> simulate(simCycles, 10);
    sched -> addProcess(nextProc);
  }

  auto t2 = chrono::system_clock::now();
  auto dur = t2 - t1;
  auto durNS = chrono::duration_cast<chrono::nanoseconds>(dur);

  for (int i = 0; i < (numCPUBound + numIOBound); i++) { //get statistics
    Process* nextProc = newQueue.front();
    newQueue.pop();

    if (nextProc -> getID() > 0) { //CPU-bound process
      CPUTime += double(nextProc -> getCPUTime());
      CPUWait += double(nextProc -> getWaitTime(simCycles));
    }

    else { //IO-bound process
      IOTime += double(nextProc -> getCPUTime());
      IOWait += double(nextProc -> getWaitTime(simCycles));
    }

    delete nextProc;
  }


  double* statArray = new double[5];

  double overhead = double(durNS.count())/numCycles;
  statArray[0] = overhead;
  
  statArray[1] = CPUTime/double(numCPUBound);
  statArray[2] = CPUWait/double(numCPUBound);
  statArray[3] = IOTime/double(numIOBound);
  statArray[4] = IOWait/double(numIOBound);

  return statArray;
}
