# This Makefile
# gives instructions to the command
# make
# about how and whether to build programs

all: pc

pc: portfoliocalculator.cpp
		g++ portfoliocalculator.cpp -o pc -lsfml-graphics -lsfml-window -lsfml-system
