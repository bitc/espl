%.o: %.asm
	nasm -g -O1 -f elf -o $@ $<

%.o: %.c
	gcc -m32 -g -nostdlib -fno-stack-protector -c -o $@ $<

EXECS=lwca lwcl

all: $(EXECS)

lwca: lwc.o start.o
	ld  -melf_i386 -o $@ $^

lwcl: lwc.c
	gcc -m32 -Wall -o lwcl lwc.c

clean:
	rm -f *.o $(EXECS)
