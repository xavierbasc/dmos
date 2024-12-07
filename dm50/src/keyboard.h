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

#define RED_SHIFT_LEFT 8
#define RED_SHIFT_WIDTH 32
#define RED_SHIFT_TOP 470
#define RED_SHIFT_HEIGHT 32

#define ONE_LEFT 60
#define ONE_WIDTH 40
#define ONE_TOP 470
#define ONE_HEIGHT 32

#define TWO_LEFT 110
#define TWO_WIDTH 40
#define TWO_TOP 470
#define TWO_HEIGHT 32

#define THREE_LEFT 160
#define THREE_WIDTH 40
#define THREE_TOP 470
#define THREE_HEIGHT 32

#define MINUS_LEFT 210
#define MINUS_WIDTH 40
#define MINUS_TOP 470
#define MINUS_HEIGHT 32


typedef enum { UNDEFINED = -1,
               ALL_CLEAR,
               ZERO,
               DECIMAL_POINT,
               EQUALS,
               PLUS,
               RED_SHIFT,
               ONE,
               TWO,
               THREE,
               MINUS } KeyPress;

KeyPress getKeyPress(int x, int y);

#endif
