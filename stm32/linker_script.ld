/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack = ORIGIN(RAM) + LENGTH(RAM);    /* end of "RAM" Ram type memory */

/* Memories definition */
MEMORY
{
  FLASH   (rx)    : ORIGIN =  0x8000000,   LENGTH = 512K
  RAM     (xrw)   : ORIGIN = 0x20000000,   LENGTH = 128K
}

/* Sections */
SECTIONS
{
  /* The startup code into "FLASH" Rom type memory */
  .isr_vector :
  {
    KEEP(*(.isr_vector)) /* Startup code */
  } >FLASH

  /* The program code and other data into "FLASH" Rom type memory */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.rodata)

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >FLASH

  /* Used by the startup to initialize data */
  _sidata = LOADADDR(.data);

  /* Initialized data sections into "RAM" Ram type memory */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */

    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
  } >RAM AT> FLASH

  /* Uninitialized data section into "RAM" Ram type memory */
  .bss :
  {
    . = ALIGN(4);
    _sbss = .;         /* define a global symbol at bss start */

    *(.bss)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
  } >RAM
}
