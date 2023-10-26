####
## \file /utils/makefile
## \author Gardier Simon
## \date 26.10.2023
## \version 2.0
####

include ../makefile.compilation

all: $(LIBUTILS)

$(LIBUTILS): utils.o
	ar rcs $(LIBUTILS) *.o

utils.o: utils.c utils.h
	$(CC) -c utils.c -o utils.o

clean:
	rm -f *.o ~* *.a