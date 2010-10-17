cc = gcc
objects = test.o simhash.o
CFLAGS = --std=c99

test : $(objects)
	$(cc) $(CFLAGS) -o test $(objects)

test.o : test.c simhash.h
	$(cc) $(CFLAGS) -c test.c

simhash.o : simhash.c simhash.h
	$(cc) $(CFLAGS) -c simhash.c

clean :
	rm test $(objects)
