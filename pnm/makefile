####
## \file /pnm/makefile
## \author Gardier Simon
## \date 26.10.2023
## \version 2.0
####

include ../makefile.compilation

all: $(LIBPNM)

$(LIBPNM): pnm.o
	ar rcs $(LIBPNM) *.o

pnm.o: pnm.c pnm.h
	$(CC) -c pnm.c -o pnm.o

clean:
	rm -f *.o ~* *.a