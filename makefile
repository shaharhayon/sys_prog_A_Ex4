CC=gcc
AR=ar
FLAGS= -Wall -g

all: frequency

frequency: frequency.o
	$(CC) $(FLAGS) -o frequency frequency.o

frequency.o: frequency.c frequency.h
	$(CC) $(FLAGS) -c frequency.c

.PHONY: clean
clean:
	rm -f frequency *.o *.a