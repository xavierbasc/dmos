CC = gcc
PLATFORM ?= linux
BUILD_TYPE ?= debug

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

# Source and object files
LIB_SRCS = $(wildcard $(LIB_SRC)/*.c) $(wildcard $(LIB_SRC)/$(PLATFORM)/*.c)
APP_SRCS = $(wildcard $(APP_SRC)/*.c) $(wildcard $(APP_SRC)/$(PLATFORM)/*.c)
APP_OBJS = $(APP_SRCS:.c=.o)
LIB_OBJS = $(LIB_SRCS:.c=.o)

# Compilation and linking options based on BUILD_TYPE
ifeq ($(BUILD_TYPE),debug)
    CFLAGS = -g -Wall -I$(LIB_INCLUDE) -I$(APP_INCLUDE)
    LDFLAGS = -L$(LIB_OUT_DIR) -ldmosd
    LIBRARY = $(LIB_OUT_DIR)/lib$(LIB_NAME)d.a
    EXECUTABLE = $(BIN_DIR)/$(PLATFORM)/$(EXEC_NAME)d
else ifeq ($(BUILD_TYPE),release)
    CFLAGS = -O2 -Wall -I$(LIB_INCLUDE) -I$(APP_INCLUDE)
    LDFLAGS = -L$(LIB_OUT_DIR) -ldmos
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
