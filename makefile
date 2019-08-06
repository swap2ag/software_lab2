#!/bin/sh
# --------------------------------------------------------
# Define required macros here
INCLUDE_DIR = .
OBJ_DIR = .
SRC_DIR = .
INCLUDES = -I "."

MAIN_OBJECTS = ps1.o ps2.o

CXXFLAGS = -Wall -g
CXX = gcc

# Rules and compilation
# Target 1 - executable
all: ps1

ps1: ps1.o
		$(CXX) $(CXXFLAGS) ps1.o -o ps1

# ps2: ps2.o
# 		$(CXX) $(CXXFLAGS) ps2.o -o ps2
		

# Target 2 - Object files					
ps1.o: ps1.c
		$(CXX) $(CXXFLAGS) -c ps1.c -o ps1.o

# ps2.o: ps2.c
# 		$(CXX) $(CXXFLAGS) -c ps2.c -o ps2.o

# Clean
.PHONY: clean
clean: 
		rm -rf *.o ps1 ps2 *.out