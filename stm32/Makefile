CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
MD5SUM=md5sum
ST-FLASH=st-flash
DFU-UTIL=dfu-util

CMSIS=../external/CMSIS

LINKER_FILE=linker_script.ld

CFLAGS=-std=c99 -Wall
CFLAGS+=-O1 -fdce -ffunction-sections -fdata-sections# Optimize for unused code
CFLAGS+=-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mabi=aapcs -mfpu=fpv4-sp-d16# ARM Cortex-M4F core with Floating point unit options
CFLAGS+=-nostdlib
CFLAGS+=-DSTM32F411xE
CFLAGS+=-I.
CFLAGS+=-I$(CMSIS)/CMSIS/Core/Include
CFLAGS+=-I$(CMSIS)/Device/ST/STM32F4/Include
CFLAGS+=-I/usr/local/Cellar/arm-none-eabi-gcc/14.2.0/lib/gcc/arm-none-eabi/14.2.0/include
CFLAGS+=-I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include
LDFLAGS=-T $(LINKER_FILE) -Wl,--fatal-warnings -Wl,--no-warn-rwx-segments -Wl,--gc-sections -Wl,--print-memory-usage

ifdef EXTRA_CFLAGS
CFLAGS+=${EXTRA_CFLAGS}
endif
ifdef EXTRA_LDFLAGS
CFLAGS+=${EXTRA_LDFLAGS}
endif

# FOR TEST:
# PROJECT=test_blink

# FOR DM50:
# PROJECT=main

PROJECT=test_blink

all: clean elf

bin: all
	$(OBJCOPY) -O binary $(PROJECT).elf $(PROJECT).bin

hex: all
	$(OBJCOPY) -O ihex $(PROJECT).elf $(PROJECT).hex

elf: startup_stm32f411xx.o system_stm32f4xx.o $(PROJECT).o
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $(PROJECT).elf

$(PROJECT).o: $(PROJECT).c
	$(CC) $(CFLAGS) -c $^

startup_stm32f411xx.o: startup_stm32f411xx.c
	$(CC) $(CFLAGS) -c $^

system_stm32f4xx.o: $(CMSIS)/Device/ST/STM32F4/Source/Templates/system_stm32f4xx.c
	$(CC) $(CFLAGS) -c $^

.PHONY: clean
clean:
	rm -f *.o $(PROJECT).elf $(PROJECT).bin $(PROJECT).hex

.PHONY: run
run: bin
	openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program $(PROJECT).bin verify reset exit"
#	$(ST-FLASH) --reset write $(PROJECT).bin 0x8000000

.PHONY: dfu
dfu: bin
	$(DFU-UTIL) -d 0483:df11 -a 0 -s 0x08000000:leave -D $(PROJECT).bin

.PHONY: external
external:
	git clone https://github.com/ARM-software/CMSIS_5.git ../external/CMSIS && \
	cd ../external/CMSIS && \
	git checkout tags/5.9.0 && \
	cd ../../ && \
	mkdir -p CMSIS/Device/ST && \
	git clone https://github.com/STMicroelectronics/cmsis_device_f4.git ../external/CMSIS/Device/ST/STM32F4 && \
	cd ../stm32
