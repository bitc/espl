.PHONY: all clean

all: scmp

clean:
	rm -f *.o scmp

scmp: scmp.o cmpstr.o
	gcc -m32 -o $@ $^

scmp.o: scmp.c
	gcc -m32 -o $@ -c $^

cmpstr.o : cmpstr.c
	gcc -m32 -o $@ -c $^
