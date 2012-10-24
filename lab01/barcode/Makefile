CC=gcc
CFLAGS=-O -g

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: encbc decbc test

test: encbc decbc testbc
	./testbc
	if [ "`./encbc shalom olam|./decbc`" != "shalom olam" ]; then\
		exit 1;\
	fi

encbc: encbc.o bclib.o
	$(CC) $(CFLAGS) -o $@ $^

decbc: decbc.o bclib.o
	$(CC) $(CFLAGS) -o $@ $^

testbc: bclib.c
	$(CC) $(CFLAGS) -o $@ -DTESTBC=1 $^

encbc.o: encbc.c bclib.h
decbc.o: decbc.c bclib.h
bclib.o: bclib.c bclib.h

clean:
	rm -f *.o encbc decbc testbc
