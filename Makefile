CC=gcc
CFLAGS=-Wall
CLIBS=-lgfortran -lm
ODIR=bin
INLIB=yellin_code/lib

all: dex
	
dex: main.o yellin_wrap.o 
	$(CC) $(CFLAGS) -o $(ODIR)/dex main.o yellin_wrap.o -L$(INLIB) -lYellinNew $(CLIBS)
	rm main.o
	rm yellin_wrap.o

main.o: src/main.c yellin_wrap.o
	$(CC) $(CFLAGS) -c src/main.c

yellin_wrap.o: src/yellin_wrap.c $(INLIB)/libYellinNew.a
	$(CC) $(CFLAGS) -c src/yellin_wrap.c 

$(INLIB)/libYellinNew.a:
	@$(MAKE) -C yellin_code

.PHONY : clean
clean :
	rm -f $(ODIR)/*
	@$(MAKE) clean -C yellin_code
