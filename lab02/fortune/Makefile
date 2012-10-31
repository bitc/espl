%.o: %.c
	gcc -c -o $@ $<

all: fortune

clean:
	rm -f *.o

fortune: fortune.o
	cc -o $@ $^
