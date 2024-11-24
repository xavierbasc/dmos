gcc-arm-none-eabi

## Macos install
brew install arm-none-eabi-gcc
brew install arm-none-eabi-gdb
brew install openocd
brew install libusb
brew install stlink

## Test blackpill (STM32F411)
```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg
```

```bash
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Wall -O2 -T stm32f4.ld -nostartfiles -nodefaultlibs -I/usr/local/Cellar/arm-none-eabi-gcc/14.2.0/lib/gcc/arm-none-eabi/14.2.0/include -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include blinky.c -o blinky.elf


arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Wall -O2 -T stm32f4.ld -nostartfiles -nodefaultlibs -I/usr/local/Cellar/arm-none-eabi-gcc/14.2.0/lib/gcc/arm-none-eabi/14.2.0/include -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include main.c -o main.elf

```

```bash
arm-none-eabi-objcopy -O binary test_blink.elf test_blink.bin

arm-none-eabi-objcopy -O binary main.elf main.bin
```

```bash
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "init" -c "halt" -c "flash erase_sector 0 0 1" -c "program blinky.hex 0x08000000 verify" -c "reset run" -c "exit"
```

## Compile
```bash
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Wall -O2 -T stm32f4.ld -nostartfiles -nodefaultlibs -I/usr/local/Cellar/arm-none-eabi-gcc/14.2.0/lib/gcc/arm-none-eabi/14.2.0/include -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include test_blink.c -o test_blink.elf


arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Wall -O2 -T stm32f4.ld -nostartfiles -nodefaultlibs -I/usr/local/Cellar/arm-none-eabi-gcc/14.2.0/lib/gcc/arm-none-eabi/14.2.0/include -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include main.c -o main.elf
```

## ELF to BIN
```bash
arm-none-eabi-objcopy -O binary test_blink.elf test_blink.bin

arm-none-eabi-objcopy -O binary main.elf main.bin

```


## Upload
```bash
st-flash --reset write test_blink.bin 0x8000000

st-flash --reset write main.bin 0x8000000
```

method 2:

```bash
openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg -c "program main.bin verify reset exit"
```
