#simple makefile for this
CC=g++
CFLAGS= -std=c++17 -g -Wall -Werror -pthread
DEPS=Strings.cpp

exercise: $(DEPS)
	$(CC) -o exercise $(CFLAGS) $(DEPS)
.PHONY: clean

clean:
	rm -f *.o exercise
	
