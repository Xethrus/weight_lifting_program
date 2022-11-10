# Makefile for Writing Make Files Example

# *****************************************************
# Variables to control Makefile operation

CC = clang++-11
CFLAGS = -Wall -g

# ****************************************************
# Targets needed to bring the executable up to date

lift_calculator: main.o
	$(CC) $(CFLAGS) -o main main.o

# The main.o target can be written more simply

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

run: main
	./main

clean:
	rm *.o main
