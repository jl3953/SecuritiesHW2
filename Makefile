CC = clang++
CXX = clang++
CXXFLAGS = -Wall -g
LDFLAGS = -g

default: addqueue showqueue rmqueue
	chmod u+s addqueue
	chmod u+s showqueue
	chmod u+s rmqueue

rmqueue: showqueuefunctions.o rmqueuefunctions.o showqueueObject.o

rmqueue.o: rmqueue.h constants.h

rmqueuefunctions.o: rmqueue.h constants.h

showqueue: showqueuefunctions.o showqueueObject.o

showqueue.o: showqueue.h constants.h

showqueueObject.o: showqueueObject.h

showqueuefunctions.o: showqueue.h constants.h

addqueue: addqueuefunctions.o

addqueue.o: addqueue.h constants.h

addqueuefunctions.o: addqueue.h constants.h


.PHONY: clean
clean:
	rm -rf *.o a.out addqueue showqueue core rmqueue

.PHONY: test
test:
	make clean
	make
	valgrind --leak-check=yes ./addqueue addqueue.cpp /home/user02/hello.txt addqueue.h
	valgrind --leak-check=yes ./showqueue
