# Compiler
CC = gcc

# Library and executable names
LIB_NAME = libUOCTaxation
EXEC_NAME = UOC20241

# Directories
LIB_DIR = UOCTaxation
LIB_INCLUDE = $(LIB_DIR)/include
LIB_SRC = $(LIB_DIR)/src
LIB_OUT_DIR = $(LIB_DIR)/lib
APP_SRC = src
APP_INCLUDE = test/include
APP_TEST_SRC = test/src
BIN_DIR = bin

# Source and object files
LIB_SRCS = $(wildcard $(LIB_SRC)/*.c)
LIB_OBJS = $(LIB_SRCS:.c=.o)
APP_SRCS = $(wildcard $(APP_SRC)/*.c) $(wildcard $(APP_TEST_SRC)/*.c)  # Include all .c files
APP_OBJS = $(APP_SRCS:.c=.o)

# Default to debug if BUILD_TYPE is not set
BUILD_TYPE ?= debug

# Compilation and linking options based on BUILD_TYPE
ifeq ($(BUILD_TYPE),debug)
    CFLAGS = -g -Wall -I$(LIB_INCLUDE) -I$(APP_INCLUDE)
    LDFLAGS = -L$(LIB_OUT_DIR) -lUOCTaxationd
    LIBRARY = $(LIB_OUT_DIR)/$(LIB_NAME)d.a
    EXECUTABLE = $(BIN_DIR)/$(EXEC_NAME)d
else ifeq ($(BUILD_TYPE),release)
    CFLAGS = -O2 -Wall -I$(LIB_INCLUDE) -I$(APP_INCLUDE)
    LDFLAGS = -L$(LIB_OUT_DIR) -lUOCTaxation
    LIBRARY = $(LIB_OUT_DIR)/$(LIB_NAME).a
    EXECUTABLE = $(BIN_DIR)/$(EXEC_NAME)
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
