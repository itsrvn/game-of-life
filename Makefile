CC = gcc
CFLAGS = -w -Wl,-subsystem,windows

HEADERS = src/constants.h src/utils.h src/grid.h
SOURCES = src/main.c src/grid.c
TARGET = game_of_life
BUILD_DIR = build

INCLUDE_PATHS = -IC:\dev\libraries\SDL2\x86\include
LIBRARY_PATHS = -LC:\dev\libraries\SDL2\x86\lib
LFLAGS = -lmingw32 -lSDL2main -lSDL2

$(TARGET) : $(SOURCES) $(HEADERS)
	if [ ! -d $(BUILD_DIR) ]; then mkdir $(BUILD_DIR); fi
	$(CC) $(SOURCES) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(CFLAGS) $(LFLAGS) -o $(BUILD_DIR)/$@

clean:
	rm -f $(BUILD_DIR)/$(TARGET)

clean-all:
	rm -rf $(BUILD_DIR)
