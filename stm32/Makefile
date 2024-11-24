# Toolchain
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# Flags
# includes search: #find /usr/local -name stdint.h
INCLUDES = -I/usr/local/Cellar/arm-none-eabi-gcc/14.2.0/lib/gcc/arm-none-eabi/14.2.0/include -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include
CFLAGS = -mcpu=cortex-m4 -mthumb -Wall -O2
LDFLAGS = -T stm32f4.ld -nostartfiles -nodefaultlibs

# Files
TARGET = main
OBJS = main.o

# Build rules
all: $(TARGET).elf

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bin:
	$(OBJCOPY) -O binary $(TARGET).elf $(TARGET).bin

flash: $(TARGET).elf
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $(TARGET).elf verify reset exit"

clean:
	rm -f $(OBJS) $(TARGET).elf
