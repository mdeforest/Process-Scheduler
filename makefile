OPTS = -Wall -std=c++11 -g

Process.o: Process.h Process.cc
	g++ ${OPTS} -c Process.cc

Scheduler.o: Scheduler.h Scheduler.cc ArrayList.h LinkedList.h LinkedListNode.h Process.h BSTNode.h BSTMultimap.h BSTForwardIterator.h
	g++ ${OPTS} -c Scheduler.cc

simulate.o: simulate.h simulate.cc Scheduler.h ArrayList.h LinkedList.h List.h LinkedListNode.h Process.h BSTNode.h BSTMultimap.h BSTForwardIterator.h
	g++ ${OPTS} -c simulate.cc

schedulesim: Scheduler.o Process.o simulate.o schedulesim.cc
	g++ ${OPTS} -o schedulesim schedulesim.cc Scheduler.o Process.o simulate.o

clean:
	rm *.o
	rm schedulesim

cleanemacs:
	rm *~

all: Process.o Scheduler.o simulate.o schedulesim
