####
## \file /tests/makefile
## \author Gardier Simon
## \date 26.10.2023
## \version 2.0
####

include ../makefile.compilation

####
## utils tests
####
UTILS_TESTS_EXEC = ../utils_tests
UTILS_TESTS_OBJECTS = ../utils/$(LIBUTILS) ../seatest/seatest.o utils_tests.o

utils_tests: $(UTILS_TESTS_OBJECTS)
	$(LD) -o $(UTILS_TESTS_EXEC) $(UTILS_TESTS_OBJECTS) $(LDFLAGS)

utils_tests.o: utils_tests.c
	$(CC) -c utils_tests.c -o utils_tests.o $(CFLAGS)

####
## lfsr tests
####
LFSR_TESTS_EXEC = ../lfsr_tests
LFSR_TESTS_OBJECTS = ../lfsr/$(LIBLFSR) ../seatest/seatest.o lfsr_tests.o

lfsr_tests: $(LFSR_TESTS_OBJECTS)
	$(LD) -o $(LFSR_TESTS_EXEC) $(LFSR_TESTS_OBJECTS) $(LDFLAGS)

lfsr_tests.o: lfsr_tests.c
	$(CC) -c lfsr_tests.c -o lfsr_tests.o $(CFLAGS)

####
##pnm tests
####
PNM_TESTS_EXEC = ../pnm_tests
PNM_TESTS_OBJECTS =  ../utils/$(LIBUTILS) ../lfsr/$(LIBLFSR) ../pnm/$(LIBPNM) ../seatest/seatest.o pnm_tests.o

pnm_tests: $(PNM_TESTS_OBJECTS)
	$(LD) -o $(PNM_TESTS_EXEC) $(PNM_TESTS_OBJECTS) $(LDFLAGS)

pnm_tests.o: pnm_tests.c
	$(CC) -c pnm_tests.c -o pnm_tests.o $(CFLAGS)

####
## shared rules
####
../utils/$(LIBUTILS): ../utils/utils.c ../utils/utils.h
	cd ../utils; make all

../pnm/$(LIBPNM): ../pnm/pnm.c ../pnm/pnm.h
	cd ../pnm; make all

../lfsr/$(LIBLFSR): ../lfsr/lfsr.c ../lfsr/lfsr.h
	cd ../lfsr; make all

../seatest/seatest.o:
	cd ../seatest; make all

clean:
	rm -f *.o $(LFSR_TESTS_EXEC) $(PNM_TESTS_EXEC) $(UTILS_TESTS_EXEC) *~
