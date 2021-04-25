CC=gfortran
CFLAGS=-fno-underscoring -frecord-marker=4 -fno-f2c -w
ODIR=bin
OLIB=lib

all: SimpleExample ExampleNew

SimpleExample: libYellin.a
	$(CC) $(CFLAGS) -o $(ODIR)/SimpleExample SimpleExample.f -L$(OLIB) -lYellin

ExampleNew: libYellinNew.a
	$(CC) $(CFLAGS) -o $(ODIR)/ExampleNew ExampleNew.f -L$(OLIB) -lYellinNew

libYellin.a:
	$(CC) $(CFLAGS) -c UpperLim.f y_vs_CLf.f CMaxinf.f ConfLev.f Cinf.f CERN_Stuff.f
	ar rcs $(OLIB)/libYellin.a UpperLim.o y_vs_CLf.o CMaxinf.o ConfLev.o Cinf.o CERN_Stuff.o
	cp CMaxf.in CMaxfLow.in y_vs_CLf.in ymintable.in CLtable.txt $(ODIR)/
	cp CMaxf.in CMaxfLow.in y_vs_CLf.in ymintable.in CLtable.txt $(OLIB)/
	rm *.o

libYellinNew.a:
	$(CC) $(CFLAGS) -c UpperLimNew.f y_vs_CLf.f CMaxinfNew.f ConfLevNew.f ConfLev.f Cinf.f CERN_Stuff.f
	ar rcs $(OLIB)/libYellinNew.a UpperLimNew.o y_vs_CLf.o CMaxinfNew.o ConfLevNew.o ConfLev.o Cinf.o CERN_Stuff.o
	cp CMaxf.in CMaxfLow.in CMaxflowNew.in ymintable.in y_vs_CLf.in CLtable.txt CLtableNew.in $(ODIR)/
	cp CMaxf.in CMaxfLow.in CMaxflowNew.in ymintable.in y_vs_CLf.in CLtable.txt CLtableNew.in $(OLIB)/
	rm *.o

.PHONY : clean
clean :
	rm -f $(ODIR)/*
	rm -f $(OLIB)/*
