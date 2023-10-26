####
## \file /program/makefile
## \author Gardier Simon
## \date 26.10.2023
## \version 2.0
####

include ../makefile.compilation

####
## ADVANCED CIPHER RULES
####
ADVANCED_CIPHER_EXEC = ../CryptLFSR
ADVANCED_CIPHER_OBJECTS = ../lfsr/$(LIBLFSR) ../utils/$(LIBUTILS) ../pnm/$(LIBPNM) crypt_lfsr_main.o

CryptLFSR: $(ADVANCED_CIPHER_OBJECTS)
	$(LD) -o $(ADVANCED_CIPHER_EXEC) $(ADVANCED_CIPHER_OBJECTS) $(LDFLAGS)

crypt_lfsr_main.o: crypt_lfsr_main.c
	$(CC) -c crypt_lfsr_main.c -o crypt_lfsr_main.o $(CFLAGS)

####
## SHARED RULES
####
../pnm/$(LIBPNM): ../pnm/pnm.c ../pnm/pnm.h
	cd ../pnm; make all

../utils/$(LIBUTILS): ../utils/utils.c ../utils/utils.h
	cd ../utils; make all

../lfsr/$(LIBLFSR): ../lfsr/lfsr.c ../lfsr/lfsr.h
	cd ../lfsr; make all

clean:
	rm -f *.o $(BASIC_CIPHER_EXEC) $(ADVANCED_CIPHER_EXEC) *~