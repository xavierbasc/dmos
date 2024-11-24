# BlackPill blink bare-bone example

This project is an attempt to produce a working code for BlackPill v3 ARM Cortex-M4F STM32F411 development board by WeAct Studio. Board description and related documents can be found [here](https://github.com/WeActStudio/WeActStudio.MiniSTM32F4x1).

The main goal of this project is to get an apprentice MCU developer a blinking BlackPill from scratch using as few proprietary and vendor specific toolchain components as possible. Therefore only _arm-gnu-toolchain_, _CMSIS_, _stlink_ / _dfu-util_, _vim_ and _GNU Make_ will be used to make all the magic to happen.

This project became possible and based on Kristian Klein-Wengel's series of blog posts "STM32 without CubeIDE" and his repository that can be found here:
- [Part 1: The bare necessities](https://kleinembedded.com/stm32-without-cubeide-part-1-the-bare-necessities)
- [Part 2: CMSIS, make and clock configuration](https://kleinembedded.com/stm32-without-cubeide-part-2-cmsis-make-and-clock-configuration)
- [Part 3: The C Standard Library and printf](https://kleinembedded.com/stm32-without-cubeide-part-3-the-c-standard-library-and-printf)
- [GitHub Repo](https://github.com/kristianklein/stm32-without-cubeide/)

But unlike the original project, this one is concentrated on getting a working firmware loaded to the BlackPill board with just a brief preceding steps explanation. Instead, more attention paid to code comments and register configuration aimed to clarify what a particular line of code and register does. Also, rework of source code and Makefile was made including some error fixing and optimization.

This project will be particularly useful for developers using GNU/Linux as host system because it focuses on toolchain for this type of host systems assuming that `make`, `git` and `st-flash` or `dfu-util` are already installed. MacOS and Windows users still can make use of this project as all used tools are available for thous platforms as well with very minor differences.

## Stages
The project is divided on several "stages" with growing complexity and functionality that utilize different MCU's hardware and peripherals. Each "stage" is placed in individual directory and can be compiled separately. 
* **1_hsi** - blink led using internal 16MHz RC as clock source and dummy for-loop delay
* **2_hse_pll** - blink led using external 25MHz crystal and PLL as clock source and tick-based delay
* **3_swo** - utilize SWO (Serial Wire Output) for printing debug messages to the host system

## Uploading firmware to MCU flash memory
To load compiled firmware to the MCU's flash memory a programmer is required. It is strongly recommended to use one of this cheap Chinese **ST-Link V2** clones because it make things much easier and faster without any manual manipulation involved. An **ST-Link V2-1** with **SWO** (Serial Wire Output) and **VCP** (Virtual COM Port) lines is even better choice. SWO allows host system to receive debug messages from a running MCU with just one extra pin used and no additional software needed. This debug messages are extremely valuable because they give an idea what's going on inside running MCU with very little effort and negligible firmware size grows. VCP provides virtual UART port without any extra devices attached to your computer USB ports allowing you to communicate with MCU using common terminal programs like `cu` for sending and receiving data while been able to flash firmware and use SWO for debugging at the same time with a single device occupying only one USB port on your host system. Beware that most of ST-Link V2 clones do not support SWO and VCP without PCB rework and firmware update. Connect ST-Link V2's SWO pin to the BlackPill's JTDO-SWO board pin B3 for the SWO debugging feature to work. For VCP connect RXD and TXD pins of ST-Link V2-1 to A2 and A3 pins of the BlackPill board respectively.

If programmer is not available, it is also possible to upload firmware on some (including described STM32F411) ST MCUs using DFU method that requires no additional hardware except USB Type-C cable and `dfu-util`. To enter DFU bootloader mode on BlackPill board it should be connected to the USB port of the host system and special button sequence mast be performed. Please, refer to section "How to enter ISP mode" of WeAct Studio board description page mentioned above.

To make firmware uploading work `st-flash` (part of _stlink_ package) or `dfu-util` should be installed and present in PATH variable of the host system.

## ARM GNU Toolchain
To cross-compile code for ARM Cortex-M4 based MCUs a set of compilation utils is required. To reduce dependency from vendors and other proprietary software, a widely used **ARM GNU Toolchain** can be relied on. A full set of compilation utils can be downloaded from this [page](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads). There is a whole bunch of different version, but we need _arm-gnu-toolchain-X.Y.relN-HOST-arm-none-eabi_. Pay attention that 'AArch32 bare-metal target (**arm-none-eabi**)' for your host OS and CPU type should be selected. For modern GNU/Linux this will be _arm-gnu-toolchain-X.Y.relN-x86\_64-arm-none-eabi.tar.xz_. This version comes with _newlib_ that will make sense later.

Download and unpack it on your host machine:
```bash
sudo tar xpf arm-gnu-toolchain-13.2.rel1-x86_64-arm-none-eabi.tar.xz -C /opt/
sudo ln -s /opt/arm-gnu-toolchain-13.2.Rel1-x86_64-arm-none-eabi /opt/arm-gnu-toolchain
```

Add path to the executable (`bin/`) and man (optional) directories to `PATH` variable of your `.bashrc`:
```bash
# arm-gnu-toolchain
PATH="$PATH:/opt/arm-gnu-toolchain/bin"
MANPATH="$MANPATH:/opt/arm-gnu-toolchain/share/man"
```

Then run `arm-none-eabi-gcc --version` command and make sure that correct GCC version is shown:
```bash
$ arm-none-eabi-gcc --version
arm-none-eabi-gcc (Arm GNU Toolchain 13.2.rel1 (Build arm-13.7)) 13.2.1 20231009
Copyright (C) 2023 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

## CMSIS
**CMSIS** (Common Microcontroller Software Interface Standard) is another mandatory part of the toolchain needed to build your own projects for STM32 MCUs. CMSIS is publicly developed and available on GitHub. CMSIS can be found [here](https://github.com/ARM-software/CMSIS_5/).

To get an actual stable version of CMSIS first clone the repo to your common STM32 projects directory. By default CMSIS is switched to the _develop_ tag when its preferable to use latest _release_ version. The actual stable release can be found at the right side of the page under Releases. Something like _CMSIS 5.9.0 Latest_ mean that tag _5.9.0_ should be considered stable. To switch to this tag go to CMSIS directory created on the previous step and checkout to the desired tag, then return to the main directory.
```bash
git clone https://github.com/ARM-software/CMSIS_5.git CMSIS
cd CMSIS
git checkout tags/5.9.0
cd ../
```
## CMSIS F4 device component
To complete minimum toolchain the CMSIS F4 device component from ST should be installed to the specific location under CMSIS directory. The component also available on GitHub and can be found [here](https://github.com/STMicroelectronics/cmsis_device_f4).

To install it, create directory called `ST` under `CMSIS/Device` and clone repo to the `STM32F4` directory:
```bash
mkdir -p CMSIS/Device/ST
git clone https://github.com/STMicroelectronics/cmsis_device_f4.git CMSIS/Device/ST/STM32F4
```

## Documentation
Before proceeding to code compilation some documents should be obtained for a close look. PDFs are available here:
- [Reference Manual](https://www.st.com/resource/en/reference_manual/rm0383-stm32f411xce-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [Datasheet](https://www.st.com/resource/en/datasheet/stm32f411ce.pdf)
- [Errata Sheet](https://www.st.com/resource/en/errata_sheet/es0287-stm32f411xcxe-device-errata-stmicroelectronics.pdf)

Many other valuable documents can be downloaded at ST's PDF page [here](https://www.st.com/en/microcontrollers-microprocessors/stm32f411/documentation.html).

## Compilation and flashing
The project repository should be cloned to the same directory where `CMSIS` is placed not to brake paths included during compilation. After all preparations are done and assuming that BlackPill is connected to ST-Link V2, it is time for the first attempt:
```bash
git clone https://github.com/e-pirate/blackpill-gcc-cmsis-blink.git
cd blackpill-gcc-cmsis-blink/1_hsi/
```
Then depending on the flashing method execute:

For the recommended **ST-Link V2** programmer:
```bash
make run
```

For the **DFU** method you should first make MCU enter the DFU mode. This may be tricky and not work all the time. Connect the BlackPill board to the host system with USB Type-C cable, then hold both NRST and BOOT0 buttons simultaneously, release NRST button and then after 0.5 seconds release BOOT0 button. To ensure that MCU entered DFU mode run `dfu-util -l` and check for lines starting with 'Found DFU' and one having something similar to "@Internal Flash  /0x08000000/04*016Kg,01*064Kg,03*128Kg".
Then execute:
```bash
make dfu
```

Don't waste you time and have fun!
