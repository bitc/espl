all: canalyze testnl testfgn

test: testnl testfgn
	./testnl
	./testfgn

testnl: testnl.o namelist.o
testfgn: testfgn.o fgetname.o

testnl.o: testnl.c namelist.h
namelist.o: namelist.c namelist.h

testfgn.o: testfgn.c fgetname.h
fgetname.o: fgetname.c fgetname.h

canalyze.o: canalyze.c fgetname.h namelist.h

canalyze: canalyze.o fgetname.o namelist.o

clean:
	rm -f canalyze testnl testfgn *.o
