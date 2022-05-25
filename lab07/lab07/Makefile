#
# Makefile for Chapter 04
#
# Type  make    to compile all the programs
# in the chapter 
#
all: spwd

spwd: spwd.o
	gcc -o spwd spwd.o

spwd.o: spwd.c
	gcc -c spwd.c

clean:
	rm -f *.o
	rm -f spwd

run: spwd
	./spwd
