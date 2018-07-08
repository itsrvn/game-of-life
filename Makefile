CC = gcc
CFLAGS = -w -Wl,-subsystem,windows

SOURCES = src/main.c src/grid.c
TARGET = game_of_life

INCLUDE_PATHS = -IC:\dev\libraries\SDL2\x86\include
LIBRARY_PATHS = -LC:\dev\libraries\SDL2\x86\lib
LFLAGS = -lmingw32 -lSDL2main -lSDL2

build/$(TARGET) : $(SOURCES)
	mkdir build
	$(CC) $(SOURCES) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CFLAGS) $(LFLAGS) -o $@

clean:
	rm -rf build
