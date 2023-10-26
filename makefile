####
## \file makefile
## \author Gardier Simon
## \date 26.10.2023
## \version 2.0
####

include makefile.compilation

.PHONY: doc all

all: CryptLFSR

CryptLFSR: utils/utils.c lfsr/lfsr.c pnm/pnm.c program/crypt_lfsr_main.c
	cd program; make CryptLFSR

tests: utils_tests lfsr_tests pnm_tests
	-./utils_tests
	-./lfsr_tests
	-./pnm_tests

utils_tests: seatest/seatest.c tests/utils_tests.c utils/utils.c utils/utils.h
	cd tests; make utils_tests

lfsr_tests: tests/utils_tests.o seatest/seatest.c tests/lfsr_tests.c lfsr/lfsr.c lfsr/lfsr.h
	cd tests; make lfsr_tests

pnm_tests: seatest/seatest.c tests/pnm_tests.c pnm/pnm.c pnm/pnm.h
	cd tests; make pnm_tests

doc: Doxyfile
	doxygen Doxyfile

clean:
	cd lfsr; make clean
	cd utils; make clean
	cd pnm; make clean
	cd program; make clean
	cd tests; make clean
	cd seatest; make clean
	rm -f *.pgm *.ppm *.pbm ~*
	rm -rf doc
