%.o: %.c
	gcc -c -o $@ $<

all: xsum

clean:
	rm -f *.o

xsum: xsum.o
	cc -o $@ $^
