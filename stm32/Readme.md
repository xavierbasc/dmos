gcc-arm-none-eabi

## Macos install
brew install arm-none-eabi-gcc
brew install arm-none-eabi-gdb
brew install openocd
brew install libusb

## Test
openocd -f interface/stlink.cfg -f target/stm32f4x.cfg

arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Wall -O2 -T stm32f4.ld -nostartfiles -nodefaultlibs -I/usr/local/Cellar/arm-none-eabi-gcc/14.2.0/lib/gcc/arm-none-eabi/14.2.0/include -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include blinky.c -o blinky.elf
arm-none-eabi-objcopy -O binary blinky.elf blinky.bin

openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "init" -c "halt" -c "flash erase_sector 0 0 1" -c "program blinky.bin 0x08000000 verify" -c "reset run" -c "exit"

## Compile
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -Wall -O2 -T stm32f4.ld -nostartfiles -nodefaultlibs -I/usr/local/Cellar/arm-none-eabi-gcc/14.2.0/lib/gcc/arm-none-eabi/14.2.0/include -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include main.c -o main.elf

## ELF to BIN
arm-none-eabi-objcopy -O binary main.elf main.bin


## Upload
openocd -f interface/stlink-v2.cfg -f target/stm32f4x.cfg -c "program main.bin verify reset exit"

