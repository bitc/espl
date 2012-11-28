.PHONY: all clean

all: scmp

clean:
	rm -f *.o scmp

scmp: scmp.o cmpstr.o
	gcc -m32 -o $@ $^

scmp.o: scmp.c
	gcc -m32 -o $@ -c $^

# C implementation:
#cmpstr.o : cmpstr.c
#	gcc -m32 -o $@ -c $^

# Assembly implementation:
cmpstr.o : cmpstr.asm
	nasm -g -f elf -o $@ $<
