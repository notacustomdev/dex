CC=gcc
CFLAGS=-Wall
CLIBS=-lgfortran -lm
ODIR=bin
INLIB=yellin_code/lib

all: dex
	echo '#!/bin/bash\n(cd $$( dirname "$${BASH_SOURCE[0]}" ) && cd yellin_code/bin/ && exec ../../bin/dex $$*)' > dex.sh
	chmod +x dex.sh
dex: main.o $(INLIB)/libYellinNew.a
	$(CC) $(CFLAGS) -o $(ODIR)/dex main.o -L$(INLIB) -lYellinNew $(CLIBS)
	cp $(INLIB)/CMaxf.in $(INLIB)/CMaxfLow.in $(INLIB)/CMaxflowNew.in $(INLIB)/ymintable.in $(INLIB)/y_vs_CLf.in $(INLIB)/CLtable.txt $(INLIB)/CLtableNew.in $(ODIR)/
	rm main.o

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c

$(INLIB)/libYellinNew.a:
	@$(MAKE) -C yellin_code

.PHONY : clean
clean :
	rm -f $(ODIR)/*
	rm dex.sh
	@$(MAKE) clean -C yellin_code
