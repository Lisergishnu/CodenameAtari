C = gcc
SDL = -framework SDL2 -framework SDL2_image -framework SDL2_ttf
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CFLAGS = -Wall -g
LDFLAGS = $(SDL)
SOURCE = src/*.c
EXE = ElevatorRescue
all:
	mkdir -p build/$(EXE).app/Contents/MacOS
	$(C) $(CFLAGS) $(SDL) $(SOURCE) -o build/$(EXE)
	mv build/$(EXE) build/$(EXE).app/Contents/MacOS
	cp etc/Info.plist build/$(EXE).app/Contents/
	cp -r img build/$(EXE).app/Contents/MacOS
	cp -r res build/$(EXE).app/Contents/MacOS
	cp -r font build/$(EXE).app/Contents/MacOS
run:
	build/$(EXE).app/Contents/MacOS/$(EXE)
clean:
	rm -rf build/
