#simple makefile for this
CC=g++
CFLAGS= -std=c++17 -g -Wall -Werror -pthread
DEPS= poly.cpp
TARGET = exercise

exercise: $(DEPS)
	$(CC) -o $(TARGET) $(CFLAGS) $(DEPS)
.PHONY: clean

clean:
	rm -f *.o $(TARGET)
	
