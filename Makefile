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

SDL2_DIR = external/SDL2
SDL2_LIB = $(SDL2_DIR)/build/.libs
SDL2_INCLUDE = $(SDL2_DIR)/include

# Source and object files
LIB_SRCS = $(wildcard $(LIB_SRC)/*.c) $(wildcard $(LIB_SRC)/$(PLATFORM)/*.c)
APP_SRCS = $(wildcard $(APP_SRC)/*.c) $(wildcard $(APP_SRC)/$(PLATFORM)/*.c)
APP_OBJS = $(APP_SRCS:.c=.o)
LIB_OBJS = $(LIB_SRCS:.c=.o)

# Compilation and linking options based on BUILD_TYPE
ifeq ($(BUILD_TYPE),debug)
    CFLAGS = -g -Wall -I$(LIB_INCLUDE) -I$(APP_INCLUDE) -I$(SDL2_INCLUDE)
    LDFLAGS = -L$(LIB_OUT_DIR) -ldmosd -L$(SDL2_LIB) -Wl,-Bstatic -lSDL2 -Wl,-Bdynamic -lm -lasound -lm -ldl -lpthread -lpulse -pthread -lsamplerate -lX11 -lXext -lXcursor -lXi -lXfixes -lXrandr -lXss -ldrm -lgbm -lwayland-egl -lwayland-client -lwayland-cursor -lxkbcommon -ldecor-0 -lpthread
    LIBRARY = $(LIB_OUT_DIR)/lib$(LIB_NAME)d.a
    EXECUTABLE = $(BIN_DIR)/$(PLATFORM)/$(EXEC_NAME)d
else ifeq ($(BUILD_TYPE),release)
    CFLAGS = -O2 -Wall -I$(LIB_INCLUDE) -I$(APP_INCLUDE) -I$(SDL2_INCLUDE)
    LDFLAGS = -L$(LIB_OUT_DIR) -ldmos -L$(SDL2_LIB) -Wl,-Bstatic -lSDL2 -Wl,-Bdynamic -lm -lasound -lm -ldl -lpthread -lpulse -pthread -lsamplerate -lX11 -lXext -lXcursor -lXi -lXfixes -lXrandr -lXss -ldrm -lgbm -lwayland-egl -lwayland-client -lwayland-cursor -lxkbcommon -ldecor-0 -lpthread
    LIBRARY = $(LIB_OUT_DIR)/lib$(LIB_NAME).a
    EXECUTABLE = $(BIN_DIR)/$(PLATFORM)/$(EXEC_NAME)
endif

# Default target: builds both library and application in debug mode
all: clean lib app

# Debug build target
debug: clean lib app

# Release build target
release: clean lib app

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
    cmake .. -DCMAKE_BUILD_TYPE=Release && \
    cmake --build . --config Release && \
    cd ../../..
