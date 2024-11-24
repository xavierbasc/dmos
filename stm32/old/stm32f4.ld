MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
  RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

SECTIONS
{
  .text : {
    *(.text*)
    *(.rodata*)
  } > FLASH

  .data : {
    *(.data*)
  } > RAM AT > FLASH

  .bss : {
    *(.bss*)
    *(COMMON)
  } > RAM

  /* Reservar espacio para el stack */
  .stack (NOLOAD) : {
    . = ALIGN(8);
    __stack_start__ = .;
    . += 0x4000;  /* Reservar 16KB para el stack */
    __stack_end__ = .;
  } > RAM
}
