%.o: %.c
	gcc -c -o $@ $<

all: invert

clean:
	rm -f *.o

invert: invert.o
	cc -o $@ $^
