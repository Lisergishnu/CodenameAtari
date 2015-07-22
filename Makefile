C = gcc
SDL = -framework SDL2 -framework SDL2_image
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CFLAGS = -Wall
LDFLAGS = $(SDL)
SOURCE = src/*.c
EXE = ElevatorRescue
all:
	mkdir -p build/
	$(C) $(CFLAGS) $(SDL) $(SOURCE) -o build/$(EXE)
	cp -r img/ build/
	cp -r res/ build/
run:
	build/$(EXE)
clean:
	rm -rf build/