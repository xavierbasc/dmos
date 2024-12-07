#ifndef KEYBOARD_H
#define KEYBOARD_H

#define AC_LEFT 8
#define AC_WIDTH 32
#define AC_TOP 518
#define AC_HEIGHT 32

#define ZERO_LEFT 60
#define ZERO_WIDTH 40
#define ZERO_TOP 518
#define ZERO_HEIGHT 32

#define DECIMAL_POINT_LEFT 110
#define DECIMAL_POINT_WIDTH 40
#define DECIMAL_POINT_TOP 518
#define DECIMAL_POINT_HEIGHT 32

#define EQUALS_LEFT 160
#define EQUALS_WIDTH 40
#define EQUALS_TOP 518
#define EQUALS_HEIGHT 32

#define PLUS_LEFT 210
#define PLUS_WIDTH 40
#define PLUS_TOP 518
#define PLUS_HEIGHT 32

typedef enum { UNDEFINED = -1,
               ALL_CLEAR,
               ZERO,
               DECIMAL_POINT,
               EQUALS,
               PLUS } KeyPress;

KeyPress getKeyPress(int x, int y);

#endif
