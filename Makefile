# MAKEFILE for BpTree 
LIB		= BpTree.cpp
OUT		= BpTree.o
CXX		=	g++
FLAGS	=
LDFLAGS = -std=c++11

ifdef debug
	FLAGS := $(FLAGS) -DDEBUG
endif

all: bptree | main 

bptree:
	$(CXX) -c $(LIB) -o $(OUT) $(FLAGS) $(LDFLAGS)

main:
	g++ main.cpp -o testRun.out $(OUT) $(FLAGS) $(LDFLAGS)

clean:
	- rm *.o
	- rm *.out
	