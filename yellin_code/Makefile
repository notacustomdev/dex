CC=gfortran
CFLAGS= -frecord-marker=4 -fno-f2c -w
ODIR=bin
OLIB=lib

all: SimpleExample ExampleNew

SimpleExample: libYellin.a
	$(CC) $(CFLAGS) -o $(ODIR)/SimpleExample SimpleExample.f -L$(OLIB) -lYellin

ExampleNew: libYellinNew.a
	$(CC) $(CFLAGS) -o $(ODIR)/ExampleNew ExampleNew.f -L$(OLIB) -lYellinNew

libYellin.a:
	$(CC) $(CFLAGS) -c UpperLim.f y_vs_CLf.f CMaxinf.f ConfLev.f Cinf.f CERN_Stuff.f
	objcopy -I binary -B i386:x86-64 CMaxf.in CMaxfin.o
	objcopy -I binary -O elf32-i386 -B i386 CMaxfLow.in CMaxfLowin.o
	objcopy -I binary -O elf32-i386 -B i386 y_vs_CLf.in y_vs_CLfin.o
	objcopy -I binary -O elf32-i386 -B i386 ymintable.in ymintablein.o
	objcopy -I binary -O elf32-i386 -B i386 CLtable.txt CLtabletxt.o
	ar rcs $(OLIB)/libYellin.a UpperLim.o y_vs_CLf.o CMaxinf.o ConfLev.o Cinf.o CERN_Stuff.o CMaxfin.o CMaxfLowin.o y_vs_CLfin.o ymintablein.o CLtabletxt.o
	rm *.o

libYellinNew.a:
	$(CC) $(CFLAGS) -c UpperLimNew.f y_vs_CLf.f CMaxinfNew.f ConfLev.f ConfLevNew.f Cinf.f CERN_Stuff.f
	objcopy -I binary -O elf64-x86-64 -B i386:x86-64 CMaxf.in CMaxfin.o
	objcopy -I binary -O elf64-x86-64 -B i386:x86-64 CMaxfLow.in CMaxfLowin.o
	objcopy -I binary -O elf64-x86-64 -B i386:x86-64 CMaxfLowNew.in CMaxfLowNewin.o
	objcopy -I binary -O elf64-x86-64 -B i386:x86-64 y_vs_CLf.in y_vs_CLfin.o
	objcopy -I binary -O elf64-x86-64 -B i386:x86-64 ymintable.in ymintablein.o
	objcopy -I binary -O elf64-x86-64 -B i386:x86-64 CLtable.txt CLtabletxt.o
	objcopy -I binary -O elf64-x86-64 -B i386:x86-64 CLtableNew.in CLtableNewin.o
	ar rcs $(OLIB)/libYellinNew.a UpperLimNew.o y_vs_CLf.o CMaxfin.o CMaxinfNew.o ConfLev.o ConfLevNew.o Cinf.o CERN_Stuff.o CMaxfLowin.o CMaxfLowNewin.o y_vs_CLfin.o ymintablein.o CLtabletxt.o CLtableNewin.o
	rm *.o

.PHONY : clean
clean :
	rm -f $(ODIR)/*
	rm -f $(OLIB)/*
