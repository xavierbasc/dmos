#ifndef KEYBOARD_H
#define KEYBOARD_H

#define AC_LEFT 8
#define AC_WIDTH 32
#define AC_TOP 518
#define AC_HEIGHT 32

#define ZERO_LEFT 64
#define ZERO_WIDTH 40
#define ZERO_TOP 518
#define ZERO_HEIGHT 32

typedef enum { UNDEFINED = -1,
               ALL_CLEAR,
               ZERO } KeyPress;

KeyPress getKeyPress(int x, int y);

#endif
