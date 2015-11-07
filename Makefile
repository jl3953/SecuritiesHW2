CC = clang++
CFLAGS = -Wall -c -g
LDFLAGS = -Wall -g

addqueue:

addqueue.o: addqueue.h


.PHONY: clean
clean:
	rm -rf *.o a.out addqueue core

.PHONY: run
run:
	make clean
	make
	valgrind --leak-check=yes ./addqueue addqueue.cpp /home/user02/hello.txt addqueue.h
