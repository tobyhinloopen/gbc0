ifndef GBDK_HOME
	GBDK_HOME = gbdk
endif

LCC = $(GBDK_HOME)/bin/lcc

all: main.gb

main.o: main.c
	$(LCC) -c -o $@ $<

main.gb: main.o
	$(LCC) -o $@ $<

clean:
	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.adb *.ihx *.lnk *.sym *.asm *.noi *.rst
