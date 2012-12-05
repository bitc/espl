%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.man: %.1
	nroff -man $< > $@

all: bsplit bmerge bsplit.man bmerge.man

bsplit: bsplit.o
	$(CC) $(LDFLAGS) -o $@ $^

bmerge: bmerge.o
	$(CC) $(LDFLAGS) -o $@ $^

bsplit.o: bsplit.c
bmerge.o: bmerge.c

clean:
	rm -f *.o 

distclean: clean
	rm -f bsplit bmerge
