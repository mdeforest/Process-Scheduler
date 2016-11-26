//schedulesim.cc

#include <iostream>
#include <string>

#include "Scheduler.h"
#include "simulate.h"

using namespace std;

int main(int argc, char** argv)
{
  /*Runs a simulation and returns the overhead, average wait times, and average 
    CPU times for each scheduler*/

  Scheduler** schedArray = new Scheduler*[4]; //array of schedulers

  RoundRobin* normalSched = new RoundRobin();
  FastRoundRobin* fastSched = new FastRoundRobin();
  CompletelyFair* fairSched = new CompletelyFair();
  FastCompletelyFair* fastFairSched = new FastCompletelyFair();

  schedArray[0] = normalSched;
  schedArray[1] = fastSched;
  schedArray[2] = fairSched;
  schedArray[3] = fastFairSched;

  string* stringArray = new string[4];
  stringArray[0] = "Overhead Norm.\tCPU CPU Norm.\tWait CPU Norm.\tCPU IO Norm.\tWait IO Norm.";
  stringArray[1] = "Overhead Fast\tCPU CPU Fast\tWait CPU Fast\tCPU IO Fast\tWait IO Fast";
  stringArray[2] = "Overhead Fair\tCPU CPU Fair\tWait CPU Fair\tCPU IO Fair\tWait IO Fair";
  stringArray[3] = "Overhead FairFast\tCPU CPU FairFast\tWait CPU FairFast\tCPU IO FairFast\tWait IO FairFast";

  int numCPUBound = atoi(argv[1]);
  int numIOBound = atoi(argv[2]);
  int numCycles = atoi(argv[3]);

  for (int i = 0; i < 4; i++){
    //Simulate each scheduler and print out the data

    double* statArray = simulate(schedArray[i], numCPUBound, numIOBound, numCycles);
    cout << stringArray[i] << endl;

    for (int j = 0; j < 5; j++) {
      cout << statArray[j] << "\t";
    }

    cout << endl;

    delete[] statArray;
  }
  
  delete normalSched;
  delete fastSched;
  delete fairSched;
  delete fastFairSched;
  delete[] schedArray;
  delete[] stringArray;
}
