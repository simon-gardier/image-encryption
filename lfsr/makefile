####
## \file /lfsr/makefile
## \author Gardier Simon
## \date 26.10.2023
## \version 2.0
####

include ../makefile.compilation

all: $(LIBLFSR)

$(LIBLFSR): lfsr.o
	ar rcs $(LIBLFSR) *.o

lfsr.o: lfsr.c lfsr.h
	$(CC) -c lfsr.c -o lfsr.o $(CFLAGS)

clean:
	rm -f *.o ~* *.a