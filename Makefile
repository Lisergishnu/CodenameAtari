CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=src/main.c
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=ElevatorRescue

all:
	mkdir -p build
	$(CC) $(SOURCES)  $(CFLAGS) -o build/$(EXECUTABLE)
	
clean:
	rm -rf build/