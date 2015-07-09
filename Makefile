# MAKEFILE for BpTree 
SRC		= BpTree.cpp
OUT		= BpTree.o
CXX		=	g++
FLAGS	=

ifdef debug
	FLAGS := $(FLAGS) -DDEBUG
endif

all: bptree

bptree:
	$(CXX) $(SRC) -o $(OUT) $(FLAGS)

clean:
	rm *.o