%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: bsplit

bsplit: bsplit.o
	$(CC) $(LDFLAGS) -o $@ $^

bsplit.o: bsplit.c

clean:
	rm -f *.o 
