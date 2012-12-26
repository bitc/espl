%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: pbsplit

pbsplit: pbsplit.o
	$(CC) $(LDFLAGS) -o $@ $^

pbsplit.o: pbsplit.c

clean:
	rm -f *.o 
