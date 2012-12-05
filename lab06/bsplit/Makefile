%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.man: %.1
	nroff -man $< > $@

all: bsplit bmerge bsplit.man bmerge.man

bsplit: bsplit.o xsum.o
	$(CC) $(LDFLAGS) -o $@ $^

bmerge: bmerge.o xsum.o
	$(CC) $(LDFLAGS) -o $@ $^

bsplit.o: bsplit.c xsum.h
bmerge.o: bmerge.c xsum.h
xsum.o: xsum.c xsum.h

clean:
	rm -f *.o 

distclean: clean
	rm -f bsplit bmerge
