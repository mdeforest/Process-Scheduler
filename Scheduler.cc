//Scheduler.cc

#include "Scheduler.h"
#include "BSTForwardIterator.h"


RoundRobin::RoundRobin()
{
  //Initializes procQueue as an empty ArrayList

  procQueue = new ArrayList<Process*>();
}

RoundRobin::~RoundRobin()
{
  //Deletes procQueue

  delete procQueue;
}

void RoundRobin::addProcess(Process* proc)
{
  //Adds the given process to the back of procQueue

  procQueue -> pushBack(proc);
}

Process* RoundRobin::popNext(int curCycle)
{
  //Pops the process at the front of the queue and returns it

  Process* temp = procQueue -> getFront();
  procQueue -> popFront();
  return temp;
}

FastRoundRobin::FastRoundRobin()
{
  delete procQueue;

  procQueue = new LinkedList<Process*>();
}

CompletelyFair::CompletelyFair()
{
  procTree = new BSTMultimap<int, Process*>();
}

CompletelyFair::~CompletelyFair()
{
  delete procTree;
}

void CompletelyFair::addProcess(Process* proc)
{
  procTree -> insert(proc -> getCPUTime(), proc);
}

Process* CompletelyFair::popNext(int curCycle)
{
  BSTForwardIterator<int, Process*> iterator = procTree -> getMin();
  
  while(iterator.getValue() -> isBlocked(curCycle)) {
    iterator.next();
  }
  
  Process* curProcess = iterator.getValue();
  procTree -> remove(iterator);

  return curProcess;
}

FastCompletelyFair::FastCompletelyFair()
{
  delete procTree;

  procTree = new RBTMultimap<int, Process*>();
  
}
