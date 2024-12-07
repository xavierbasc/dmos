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

#define POWER_TEN_LEFT 8
#define POWER_TEN_WIDTH 40
#define POWER_TEN_TOP 334
#define POWER_TEN_HEIGHT 32

#define PI_LEFT 52
#define PI_WIDTH 40
#define PI_TOP 334
#define PI_HEIGHT 32

#define CHANGE_SIGN_LEFT 96
#define CHANGE_SIGN_WIDTH 40
#define CHANGE_SIGN_TOP 334
#define CHANGE_SIGN_HEIGHT 32

#define LEFT_BRACKET_LEFT 140
#define LEFT_BRACKET_WIDTH 40
#define LEFT_BRACKET_TOP 334
#define LEFT_BRACKET_HEIGHT 32

#define RIGHT_BRACKET_LEFT 184
#define RIGHT_BRACKET_WIDTH 40
#define RIGHT_BRACKET_TOP 334
#define RIGHT_BRACKET_HEIGHT 32

#define LIBRARY_LEFT 228
#define LIBRARY_WIDTH 40
#define LIBRARY_TOP 334
#define LIBRARY_HEIGHT 32

#define SINE_LEFT 8
#define SINE_WIDTH 40
#define SINE_TOP 290
#define SINE_HEIGHT 32

#define COSINE_LEFT 52
#define COSINE_WIDTH 40
#define COSINE_TOP 290
#define COSINE_HEIGHT 32

#define TANGENT_LEFT 96
#define TANGENT_WIDTH 40
#define TANGENT_TOP 290
#define TANGENT_HEIGHT 32

#define FRACTION_LEFT 140
#define FRACTION_WIDTH 40
#define FRACTION_TOP 290
#define FRACTION_HEIGHT 32

#define DOWN_LEFT 184
#define DOWN_WIDTH 40
#define DOWN_TOP 290
#define DOWN_HEIGHT 32

#define BACK_LEFT 228
#define BACK_WIDTH 40
#define BACK_TOP 290
#define BACK_HEIGHT 32

#define SQUARE_ROOT_LEFT 8
#define SQUARE_ROOT_WIDTH 40
#define SQUARE_ROOT_TOP 246
#define SQUARE_ROOT_HEIGHT 32

#define SQUARE_LEFT 52
#define SQUARE_WIDTH 40
#define SQUARE_TOP 246
#define SQUARE_HEIGHT 32

#define LOGARITHM_LEFT 96
#define LOGARITHM_WIDTH 40
#define LOGARITHM_TOP 246
#define LOGARITHM_HEIGHT 32

#define LEFT_LEFT 140
#define LEFT_WIDTH 40
#define LEFT_TOP 246
#define LEFT_HEIGHT 32

#define OK_LEFT 184
#define OK_WIDTH 40
#define OK_TOP 246
#define OK_HEIGHT 32

#define RIGHT_LEFT 228
#define RIGHT_WIDTH 40
#define RIGHT_TOP 246
#define RIGHT_HEIGHT 32


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
               QUOTIENT,
               POWER_TEN,
               PI,
               CHANGE_SIGN,
               LEFT_BRACKET,
               RIGHT_BRACKET,
               LIBRARY,
               SINE,
               COSINE,
               TANGENT,
               FRACTION,
               DOWN,
               BACK,
               SQUARE_ROOT,
               SQUARE,
               LOGARITHM,
               LEFT,
               OK,
               RIGHT} KeyPress;

KeyPress getKeyPress(int x, int y);

#endif
