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

#define BLUE_SHIFT_LEFT 8
#define BLUE_SHIFT_WIDTH 32
#define BLUE_SHIFT_TOP 428
#define BLUE_SHIFT_HEIGHT 32

#define FOUR_LEFT 60
#define FOUR_WIDTH 40
#define FOUR_TOP 428
#define FOUR_HEIGHT 32

#define FIVE_LEFT 110
#define FIVE_WIDTH 40
#define FIVE_TOP 428
#define FIVE_HEIGHT 32

#define SIX_LEFT 160
#define SIX_WIDTH 40
#define SIX_TOP 428
#define SIX_HEIGHT 32

#define PRODUCT_LEFT 210
#define PRODUCT_WIDTH 40
#define PRODUCT_TOP 428
#define PRODUCT_HEIGHT 32


#define YELLOW_SHIFT_LEFT 8
#define YELLOW_SHIFT_WIDTH 32
#define YELLOW_SHIFT_TOP 380
#define YELLOW_SHIFT_HEIGHT 32

#define SEVEN_LEFT 60
#define SEVEN_WIDTH 40
#define SEVEN_TOP 380
#define SEVEN_HEIGHT 32

#define EIGHT_LEFT 110
#define EIGHT_WIDTH 40
#define EIGHT_TOP 380
#define EIGHT_HEIGHT 32

#define NINE_LEFT 160
#define NINE_WIDTH 40
#define NINE_TOP 380
#define NINE_HEIGHT 32

#define QUOTIENT_LEFT 210
#define QUOTIENT_WIDTH 40
#define QUOTIENT_TOP 380
#define QUOTIENT_HEIGHT 32


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
               MINUS,
               BLUE_SHIFT,
               FOUR,
               FIVE,
               SIX,
               PRODUCT,
               YELLOW_SHIFT,
               SEVEN,
               EIGHT,
               NINE,
               QUOTIENT} KeyPress;

KeyPress getKeyPress(int x, int y);

#endif
