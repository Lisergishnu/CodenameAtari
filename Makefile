VERSION=v1.1
C = gcc
SDL = -framework SDL2 -framework SDL2_image -framework SDL2_ttf -framework SDL2_mixer -framework CoreFoundation
# If your compiler is a bit older you may need to change -std=c++11 to -std=c++0x
CFLAGS = -Wall -o2
LDFLAGS = $(SDL)
SOURCE = src/*.c
EXE = ElevatorRescue
OBJECTS = main.o video.o game.o
# WIN32 compilation flags
SDL_ROOT_DIR = /usr/local/SDL2-mingw/x86_64-w64-mingw32
WIN32C = /usr/local/mingw/bin/x86_64-w64-mingw32-gcc
WIN32CFLAGS = `$(SDL_ROOT_DIR)/bin/sdl2-config --cflags`
WIN32LDFLAGS = `$(SDL_ROOT_DIR)/bin/sdl2-config --libs` \
							 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -static-libgcc -static-libstdc++
WIN32EXE = $(EXE).exe

all:	
	mkdir -p build/$(EXE).app/Contents/MacOS
	$(C) $(CFLAGS) $(SDL) $(SOURCE) -o build/$(EXE)
	mv build/$(EXE) build/$(EXE).app/Contents/MacOS
	cp etc/Info.plist build/$(EXE).app/Contents/
	mkdir -p build/$(EXE).app/Contents/Resources
	cp -r img build/$(EXE).app/Contents/Resources
	cp -r res build/$(EXE).app/Contents/Resources
	cp -r font build/$(EXE).app/Contents/Resources
	cp -r snd build/$(EXE).app/Contents/Resources
	cp -r etc/er.icns build/$(EXE).app/Contents/Resources
	cp -rf /Library/Frameworks/SDL2*.framework build/$(EXE).app/Contents/Resources
win32: 
	mkdir -p build-win32
	$(WIN32C) $(WIN32CFLAGS) $(CFLAGS) $(SOURCE) $(WIN32LDFLAGS) -o build-win32/$(WIN32EXE)
	cp bin/*.dll build-win32/
	cp -r img build-win32/
	cp -r res build-win32/
	cp -r font build-win32/
	cp -r snd build-win32/
	rm -f build-win32/$(EXE)-$(VERSION).zip
	zip -r $(EXE)-$(VERSION).zip build-win32
	mv $(EXE)-$(VERSION).zip build-win32/
run:
	build/$(EXE).app/Contents/MacOS/$(EXE)
clean:
	rm -rf build/
	rm -rf build-win32/
