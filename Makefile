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
else
    # Configuración por defecto para Linux
    SDL2_LIB = external/SDL2/build
    LDFLAGS_SDL = -I$(SDL2_INCLUDE) Wl,-Bstatic -lSDL2 -Wl,-Bdynamic -lm -lasound -lm -ldl -lpthread -lpulse -pthread -lsamplerate -lX11 -lXext -lXcursor -lXi -lXfixes -lXrandr -lXss -ldrm -lgbm -lwayland-egl -lwayland-client -lwayland-cursor -lxkbcommon -ldecor-0 -lpthread
endif

# Source and object files
LIB_SRCS = $(wildcard $(LIB_SRC)/*.c) $(wildcard $(LIB_SRC)/$(PLATFORM)/*.c)
APP_SRCS = $(wildcard $(APP_SRC)/*.c) $(wildcard $(APP_SRC)/$(PLATFORM)/*.c)
APP_OBJS = $(APP_SRCS:.c=.o)
LIB_OBJS = $(LIB_SRCS:.c=.o)

LDFLAGS = -L$(LIB_OUT_DIR) -ldmos -L$(SDL2_LIB) $(LDFLAGS_SDL) 
LIBRARY = $(LIB_OUT_DIR)/lib$(LIB_NAME).a
EXECUTABLE = $(BIN_DIR)/$(PLATFORM)/$(EXEC_NAME)

ifeq ($(BUILD_TYPE),debug)
    CFLAGS += -g -Wall
else ifeq ($(BUILD_TYPE),release)
    CFLAGS += -O2 -Wall
endif

# Default target: builds both library and application in debug mode
all: clean lib app

# Debug build target
debug: clean lib app

# Release build target
release: clean lib app run

# Build the library
lib: $(LIBRARY)

$(LIBRARY): $(LIB_OBJS) | $(LIB_OUT_DIR)
	ar rcs $@ $(LIB_OBJS)

# Build the application
app: $(EXECUTABLE)

$(EXECUTABLE): $(APP_OBJS) $(LIBRARY) | $(BIN_DIR)
	$(CC) $(APP_OBJS) -o $@ $(LDFLAGS)

# Create output directories if they don't exist
$(LIB_OUT_DIR) $(BIN_DIR):
	mkdir -p $@

# Clean up object files and output
clean:
	rm -f $(LIB_OBJS) $(APP_OBJS) $(LIBRARY) $(EXECUTABLE)

# Run the application
run: app
	$(EXECUTABLE)

external:
    git clone --depth=1 --branch release-2.30.9 https://github.com/libsdl-org/SDL.git external/SDL2 && \
    cd external/SDL2 && \
    mkdir build && cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    cmake --build . --config Release && \
    cd ../../..
