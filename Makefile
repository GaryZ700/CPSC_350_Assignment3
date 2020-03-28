# Gary Zeri
# ID: 2321569
# zeri@chapman.edu
# CPSC 250-02
# Assignment 3: Syntax Checker

#change this to the correct assignment #
EXECUTABLE := assignment3

# the source files to be built
SOURCES := *.cpp

#stuff you don't need to worry about
INCLUDES := -I ../include
EXT := exe
CC := g++

all:
	$(CC) $(INCLUDES) $(SOURCES) -o $(EXECUTABLE).$(EXT)

realclean:
	find . -type f -name "*.o" -exec rm '{}' \;
	find . -type f -name "*.exe" -exec rm '{}' \;

# this line required by make - don't delete
