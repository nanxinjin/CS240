all: mytest

problem=problem_classes.h
CC=g++ -std=c++11 -g

mytest: mytest.cpp $(problem) classes.cpp
	$(CC) -o mytest mytest.cpp classes.cpp

clean:
	rm -f *.o *.out *.txt mytest 
