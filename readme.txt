Michaela DeForest
CPS 222 Project 2

Files submitted:
List.h
ArrayList.h
LinkedList.h
LinkedListNode.h
Process.h
Process.cc
Scheduler.h
Scheduler.cc
BSTMultimap.h
BSTNode.h
BSTForwardIterator.h
RBTNode.h
RBTMultimap.h
simulate.h
simulate.cc
schedulesim.cc
makefile
timing.pdf
cputimes.pdf
Homework 2 Cover Sheet.pdf
readme.txt

This project contains one main program with many components. The command 'make 
all' will compile the entire project. Alternatively, you may compile according
to the directions below.

---schedulesim---
To compile: make schedulesim
To run: ./schedulesim <number of CPU-bound processes> <number of I/O-bound
   processes> <number of cycles to simulate>
Description:
The schedulesim program is a program intended to simulate 4 types of schedulers (ArrayList, LinkedList, BSTMultimap, RBTMultimap) and output the statistics
related to each scheduler simulation. When running the program, give the <number
of CPU-bound processes> and the <number of I/O-bound processes> that you want
to simulate for a specific <number of cycles>.

Known issues:

-No known issues, although makefile may include/not include certain elements
