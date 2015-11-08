CC = clang++
CFLAGS = -Wall -c -g
LDFLAGS = -Wall -g

default: addqueue showqueue

showqueue:

showqueue.o: showqueue.h

addqueue:

addqueue.o: addqueue.h


.PHONY: clean
clean:
	rm -rf *.o a.out addqueue showqueue core

.PHONY: run
test:
	make clean
	make
	valgrind --leak-check=yes ./addqueue addqueue.cpp /home/user02/hello.txt addqueue.h
