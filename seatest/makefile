####
## \file /seatest/makefile
## \author Gardier Simon
## \date 26.10.2023
## \version 2.0
####

include ../makefile.compilation

all: seatest.o

seatest.o: seatest.c seatest.h
	$(CC) -c seatest.c -o seatest.o

clean:
	rm -f *.o ~*