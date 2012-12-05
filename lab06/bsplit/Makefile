CFLAGS = -m32
LDFLAGS = -m32

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.man: %.1
	nroff -man $< > $@

all: bsplit bmerge bsplit.man bmerge.man

bsplit: bsplit.o bsplit_asm.o
	$(CC) $(LDFLAGS) -o $@ $^

bmerge: bmerge.o
	$(CC) $(LDFLAGS) -o $@ $^

bsplit.o: bsplit.c
bmerge.o: bmerge.c

bsplit_asm.o : bsplit_asm.asm
	nasm -g -f elf -o $@ $<

clean:
	rm -f *.o 

distclean: clean
	rm -f bsplit bmerge
