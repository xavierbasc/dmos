# Variables generales
APP_NAME := dm50
SRC_DIR := dm50/src
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

XCODE_BUILD_DIR := $(BUILD_DIR)/macos

CC := gcc
CFLAGS := -Wall -g -O2
LDFLAGS := Wl,-Bstatic -lSDL2 -Wl,-Bdynamic
PLATFORM := native

# Definiciones específicas de plataforma
ifeq ($(PLATFORM), macos)
    BUILD_CMD := xcodebuild -project macos/dm50.xcodeproj -scheme macOS -configuration Release -derivedDataPath $(XCODE_BUILD_DIR)
    MAKE_INSTALLER_CMD := pkgbuild --min-os-version 13.5 --root $(XCODE_BUILD_DIR)/Build/Products/Release --identifier "dm50.macos" --version 1.0 build/DM50.pkg
else ifeq ($(PLATFORM), linux)
    CC := gcc
    CFLAGS += -lSDL2
else ifeq ($(PLATFORM), windows)
    CC := x86_64-w64-mingw32-gcc
    CFLAGS += -lmingw32 -lSDL2main -lSDL2
    BIN_EXT := .exe
else ifeq ($(PLATFORM), stm32)
    CC := arm-none-eabi-gcc
    CFLAGS := -mcpu=cortex-m4 -mthumb -g -Os -ffunction-sections -fdata-sections
    LDFLAGS := -T stm32.ld -nostartfiles -Wl,--gc-sections
else ifeq ($(PLATFORM), ios)
    CC := clang
    CFLAGS := -isysroot $(shell xcrun --sdk iphoneos --show-sdk-path) -arch arm64 -fobjc-arc
    LDFLAGS := -framework SDL2 -framework UIKit
else ifeq ($(PLATFORM), android)
    CC := $(NDK_PATH)/toolchains/llvm/prebuilt/linux-x86_64/bin/clang
    CFLAGS := -target aarch64-linux-android21 -fPIE
    LDFLAGS := -llog -landroid
endif

all: build

build:
ifeq ($(PLATFORM), macos)
	$(BUILD_CMD)
else
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(APP_NAME) src/main.c
endif

install-macos: build
	@echo "DMG ..."
	create-dmg --app-drop-link 50 50 build/dm50.dmg build/macos/Build/Products/Release/macOS.app

clean:
ifeq ($(PLATFORM), macos)
	rm -rf $(XCODE_BUILD_DIR)
else
	rm -rf $(BUILD_DIR)
endif

.PHONY: all build clean install-macos
