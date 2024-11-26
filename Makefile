SHELL := /bin/bash

.PHONY: all clean debug release run external lib app

CC = gcc
PLATFORM ?= linux
BUILD_TYPE ?= release

# Library and executable names
LIB_NAME = dmos
EXEC_NAME = dm50

# Directories
LIB_DIR = dmos
LIB_SRC = $(LIB_DIR)/src
LIB_INCLUDE = $(LIB_DIR)/include
LIB_OUT_DIR = $(LIB_DIR)/lib

APP_DIR = dm50
APP_SRC = $(APP_DIR)/src
APP_INCLUDE = $(APP_DIR)/include/
BIN_DIR = $(APP_DIR)/bin

# Configuración de SDL2 según el sistema operativo
ifeq ($(PLATFORM),macos)
    # Enlazar con SDL2 desde el sistema en macOS
    SDL2_LIB = -F/Library/Frameworks
    SDL2_INCLUDE = /Library/Frameworks/SDL2.framework/Headers
    LDFLAGS_SDL = -framework SDL2
else ifeq ($(PLATFORM),windows)
    # Ejemplo: Ruta SDL2 en Windows (ajustar según configuración)
    SDL2_LIB = -lSDL2
    SDL2_INCLUDE = C:/path/to/SDL2/include
    LDFLAGS_SDL = -L/path/to/SDL2/lib -lSDL2
else ifeq ($(PLATFORM),linux)
    # Ejemplo: Ruta SDL2 en Windows (ajustar según configuración)
    # Configuración por defecto para Linux
    SDL2_LIB = ./external/SDL2/build
    SDL2_INCLUDE = ./external/SDL2/include/
    LDFLAGS_SDL = -lSDL2 -Wl,-Bdynamic -lm -lasound -lm -ldl -lpthread -lpulse -pthread -lsamplerate -lX11 -lXext -lXcursor -lXi -lXfixes -lXrandr -lXss -ldrm -lgbm -lwayland-egl -lwayland-client -lwayland-cursor -lxkbcommon -ldecor-0 -lpthread

endif

ifeq ($(BUILD_TYPE),debug)
    CFLAGS += -g -Wall -I$(SDL2_INCLUDE)
else ifeq ($(BUILD_TYPE),release)
    CFLAGS += -O2 -Wall -I$(SDL2_INCLUDE)
endif


# Default target: builds both library and application in debug mode
all: clean lib app

# Debug build target
debug: clean lib app

# Release build target
release: lib app run

# Build the library
lib: $(LIBRARY)

$(LIBRARY): $(LIB_OBJS) | $(LIB_OUT_DIR)
	ar rcs $@ $(LIB_OBJS)
	@echo LDFLAGS $(LDFLAGS)

# Build the application
app: $(EXECUTABLE) 

$(EXECUTABLE): external $(APP_OBJS) $(LIBRARY) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(APP_OBJS) -o $@ $(LDFLAGS)

# Create output directories if they don't exist
$(LIB_OUT_DIR) $(BIN_DIR):
	mkdir -p $@

# Clean up object files and output

clean:
ifeq ($(PLATFORM), macos)
	rm -rf $(XCODE_BUILD_DIR)
else
	rm -rf $(BUILD_DIR)
endif

external:
	if [ -d "external" ]; then \
		echo external exists; \
	else \
		echo "SDL2 downloading..."; \
		git clone --depth=1 --branch release-2.30.9 https://github.com/libsdl-org/SDL.git external/SDL2 && \
		cd external/SDL2 && \
		mkdir build && cd build && \
		cmake .. -DCMAKE_BUILD_TYPE=Release && \
		cmake --build . --config Release && \
		cd ../../..;\
	fi\
	
.PHONY: external

