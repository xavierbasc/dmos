#include "keyboard.h"

KeyPress getKeyPress(int x, int y)
{
    if (AC_LEFT <= x && x <= AC_LEFT + AC_WIDTH && AC_TOP <= y && y <= AC_TOP + AC_HEIGHT)    
    { 
        return ALL_CLEAR;
    }
    else if (ZERO_LEFT <= x && x <= ZERO_LEFT + ZERO_WIDTH && ZERO_TOP <= y && y <= ZERO_TOP + ZERO_HEIGHT)    
    {
        return ZERO;
    }
    else if (DECIMAL_POINT_LEFT <= x && x <= DECIMAL_POINT_LEFT + DECIMAL_POINT_WIDTH && DECIMAL_POINT_TOP <= y && y <= DECIMAL_POINT_TOP + DECIMAL_POINT_HEIGHT)    
    {
        return DECIMAL_POINT;
    }
    else if (EQUALS_LEFT <= x && x <= EQUALS_LEFT + EQUALS_WIDTH && EQUALS_TOP <= y && y <= EQUALS_TOP + EQUALS_HEIGHT)    
    {
        return EQUALS;
    }
    else if (PLUS_LEFT <= x && x <= PLUS_LEFT + PLUS_WIDTH && PLUS_TOP <= y && y <= PLUS_TOP + PLUS_HEIGHT)    
    {
        return PLUS;
    }
    else if (RED_SHIFT_LEFT <= x && x <= RED_SHIFT_LEFT + RED_SHIFT_WIDTH && RED_SHIFT_TOP <= y && y <= RED_SHIFT_TOP + RED_SHIFT_HEIGHT)    
    {
        return RED_SHIFT;
    }
    else if (ONE_LEFT <= x && x <= ONE_LEFT + ONE_WIDTH && ONE_TOP <= y && y <= ONE_TOP + ONE_HEIGHT)    
    {
        return ONE;
    }
    else if (TWO_LEFT <= x && x <= TWO_LEFT + TWO_WIDTH && TWO_TOP <= y && y <= TWO_TOP + TWO_HEIGHT)    
    {
        return TWO;
    }
    else if (THREE_LEFT <= x && x <= THREE_LEFT + THREE_WIDTH && THREE_TOP <= y && y <= THREE_TOP + THREE_HEIGHT)    
    {
        return THREE;
    }
    else if (MINUS_LEFT <= x && x <= MINUS_LEFT + MINUS_WIDTH && MINUS_TOP <= y && y <= MINUS_TOP + MINUS_HEIGHT)    
    {
        return MINUS;
    }
    else if (BLUE_SHIFT_LEFT <= x && x <= BLUE_SHIFT_LEFT + BLUE_SHIFT_WIDTH && BLUE_SHIFT_TOP <= y && y <= BLUE_SHIFT_TOP + BLUE_SHIFT_HEIGHT)    
    {
        return BLUE_SHIFT;
    }
    else if (FOUR_LEFT <= x && x <= FOUR_LEFT + FOUR_WIDTH && FOUR_TOP <= y && y <= FOUR_TOP + FOUR_HEIGHT)    
    {
        return FOUR;
    }
    else if (FIVE_LEFT <= x && x <= FIVE_LEFT + FIVE_WIDTH && FIVE_TOP <= y && y <= FIVE_TOP + FIVE_HEIGHT)    
    {
        return FIVE;
    }
    else if (SIX_LEFT <= x && x <= SIX_LEFT + SIX_WIDTH && SIX_TOP <= y && y <= SIX_TOP + SIX_HEIGHT)    
    {
        return SIX;
    }
    else if (PRODUCT_LEFT <= x && x <= PRODUCT_LEFT + PRODUCT_WIDTH && PRODUCT_TOP <= y && y <= PRODUCT_TOP + PRODUCT_HEIGHT)    
    {
        return PRODUCT;
    }
    else if (YELLOW_SHIFT_LEFT <= x && x <= YELLOW_SHIFT_LEFT + YELLOW_SHIFT_WIDTH && YELLOW_SHIFT_TOP <= y && y <= YELLOW_SHIFT_TOP + YELLOW_SHIFT_HEIGHT)    
    {
        return YELLOW_SHIFT;
    }
    else if (SEVEN_LEFT <= x && x <= SEVEN_LEFT + SEVEN_WIDTH && SEVEN_TOP <= y && y <= SEVEN_TOP + SEVEN_HEIGHT)    
    {
        return SEVEN;
    }
    else if (EIGHT_LEFT <= x && x <= EIGHT_LEFT + EIGHT_WIDTH && EIGHT_TOP <= y && y <= EIGHT_TOP + EIGHT_HEIGHT)    
    {
        return EIGHT;
    }
    else if (NINE_LEFT <= x && x <= NINE_LEFT + NINE_WIDTH && NINE_TOP <= y && y <= NINE_TOP + NINE_HEIGHT)    
    {
        return NINE;
    }
    else if (QUOTIENT_LEFT <= x && x <= QUOTIENT_LEFT + QUOTIENT_WIDTH && QUOTIENT_TOP <= y && y <= QUOTIENT_TOP + QUOTIENT_HEIGHT)    
    {
        return QUOTIENT;
    }
    else if (POWER_TEN_LEFT <= x && x <= POWER_TEN_LEFT + POWER_TEN_WIDTH && POWER_TEN_TOP <= y && y <= POWER_TEN_TOP + POWER_TEN_HEIGHT)    
    {
        return POWER_TEN;
    }
    else if (PI_LEFT <= x && x <= PI_LEFT + PI_WIDTH && PI_TOP <= y && y <= PI_TOP + PI_HEIGHT)    
    {
        return PI;
    }
    else if (CHANGE_SIGN_LEFT <= x && x <= CHANGE_SIGN_LEFT + CHANGE_SIGN_WIDTH && CHANGE_SIGN_TOP <= y && y <= CHANGE_SIGN_TOP + CHANGE_SIGN_HEIGHT)    
    {
        return CHANGE_SIGN;
    }
    else if (LEFT_BRACKET_LEFT <= x && x <= LEFT_BRACKET_LEFT + LEFT_BRACKET_WIDTH && LEFT_BRACKET_TOP <= y && y <= LEFT_BRACKET_TOP + LEFT_BRACKET_HEIGHT)    
    {
        return LEFT_BRACKET;
    }
    else if (RIGHT_BRACKET_LEFT <= x && x <= RIGHT_BRACKET_LEFT + RIGHT_BRACKET_WIDTH && RIGHT_BRACKET_TOP <= y && y <= RIGHT_BRACKET_TOP + RIGHT_BRACKET_HEIGHT)    
    {
        return RIGHT_BRACKET;
    }
    else if (LIBRARY_LEFT <= x && x <= LIBRARY_LEFT + LIBRARY_WIDTH && LIBRARY_TOP <= y && y <= LIBRARY_TOP + LIBRARY_HEIGHT)    
    {
        return LIBRARY;
    }
    else if (SINE_LEFT <= x && x <= SINE_LEFT + SINE_WIDTH && SINE_TOP <= y && y <= SINE_TOP + SINE_HEIGHT)    
    {
        return SINE;
    }
    else if (COSINE_LEFT <= x && x <= COSINE_LEFT + COSINE_WIDTH && COSINE_TOP <= y && y <= COSINE_TOP + COSINE_HEIGHT)    
    {
        return COSINE;
    }
    else if (TANGENT_LEFT <= x && x <= TANGENT_LEFT + TANGENT_WIDTH && TANGENT_TOP <= y && y <= TANGENT_TOP + TANGENT_HEIGHT)    
    {
        return TANGENT;
    }
    else if (FRACTION_LEFT <= x && x <= FRACTION_LEFT + FRACTION_WIDTH && FRACTION_TOP <= y && y <= FRACTION_TOP + FRACTION_HEIGHT)    
    {
        return FRACTION;
    }
    else if (DOWN_LEFT <= x && x <= DOWN_LEFT + DOWN_WIDTH && DOWN_TOP <= y && y <= DOWN_TOP + DOWN_HEIGHT)    
    {
        return DOWN;
    }
    else if (BACK_LEFT <= x && x <= BACK_LEFT + BACK_WIDTH && BACK_TOP <= y && y <= BACK_TOP + BACK_HEIGHT)    
    {
        return BACK;
    }
    else if (SQUARE_ROOT_LEFT <= x && x <= SQUARE_ROOT_LEFT + SQUARE_ROOT_WIDTH && SQUARE_ROOT_TOP <= y && y <= SQUARE_ROOT_TOP + SQUARE_ROOT_HEIGHT)    
    {
        return SQUARE_ROOT;
    }
    else if (SQUARE_LEFT <= x && x <= SQUARE_LEFT + SQUARE_WIDTH && SQUARE_TOP <= y && y <= SQUARE_TOP + SQUARE_HEIGHT)    
    {
        return SQUARE;
    }
    else if (LOGARITHM_LEFT <= x && x <= LOGARITHM_LEFT + LOGARITHM_WIDTH && LOGARITHM_TOP <= y && y <= LOGARITHM_TOP + LOGARITHM_HEIGHT)    
    {
        return LOGARITHM;
    }
    else if (LEFT_LEFT <= x && x <= LEFT_LEFT + LEFT_WIDTH && LEFT_TOP <= y && y <= LEFT_TOP + LEFT_HEIGHT)    
    {
        return LEFT;
    }
    else if (OK_LEFT <= x && x <= OK_LEFT + OK_WIDTH && OK_TOP <= y && y <= OK_TOP + OK_HEIGHT)    
    {
        return OK;
    }
    else if (RIGHT_LEFT <= x && x <= RIGHT_LEFT + RIGHT_WIDTH && RIGHT_TOP <= y && y <= RIGHT_TOP + RIGHT_HEIGHT)    
    {
        return RIGHT;
    }
    
    return UNDEFINED; 
}
