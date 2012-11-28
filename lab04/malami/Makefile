.PHONY: all clean dist
.SUFFIXES: .c .o .h .asm

all: test_malami

CFLAGS=-g -m32 -O0 -Wall
LDFLAGS=$(CFLAGS)


%.o: %.asm
	nasm -g -f elf -o $@ $<

%.o: %.c
	gcc $(CFLAGS) -c $<

test_malami: test_malami.o malami.o
	gcc $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o *~
