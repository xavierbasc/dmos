//NAME: keyboard.h
//PURPOSE: Header for mapping from x,y coordinates to keypressess
//AUTHOR: Damien Sticklen
//DATE: 2024-12-07

#include "keyboard.h"

//Converts an x,y coordinate to a recognised keypress
//TODO: Recompute x,y values based on scaling
KeyPress getKeyPress(int x, int y)
{
    if (AC_X_POS <= x && x <= AC_X_POS + AC_WIDTH && AC_Y_POS <= y && y <= AC_Y_POS + AC_HEIGHT)    
    { 
        return ALL_CLEAR;
    }
    else if (ZERO_X_POS <= x && x <= ZERO_X_POS + ZERO_WIDTH && ZERO_Y_POS <= y && y <= ZERO_Y_POS + ZERO_HEIGHT)    
    {
        return ZERO;
    }
    else if (DECIMAL_POINT_X_POS <= x && x <= DECIMAL_POINT_X_POS + DECIMAL_POINT_WIDTH && DECIMAL_POINT_Y_POS <= y && y <= DECIMAL_POINT_Y_POS + DECIMAL_POINT_HEIGHT)    
    {
        return DECIMAL_POINT;
    }
    else if (EQUALS_X_POS <= x && x <= EQUALS_X_POS + EQUALS_WIDTH && EQUALS_Y_POS <= y && y <= EQUALS_Y_POS + EQUALS_HEIGHT)    
    {
        return EQUALS;
    }
    else if (PLUS_X_POS <= x && x <= PLUS_X_POS + PLUS_WIDTH && PLUS_Y_POS <= y && y <= PLUS_Y_POS + PLUS_HEIGHT)    
    {
        return PLUS;
    }
    else if (RED_SHIFT_X_POS <= x && x <= RED_SHIFT_X_POS + RED_SHIFT_WIDTH && RED_SHIFT_Y_POS <= y && y <= RED_SHIFT_Y_POS + RED_SHIFT_HEIGHT)    
    {
        return RED_SHIFT;
    }
    else if (ONE_X_POS <= x && x <= ONE_X_POS + ONE_WIDTH && ONE_Y_POS <= y && y <= ONE_Y_POS + ONE_HEIGHT)    
    {
        return ONE;
    }
    else if (TWO_X_POS <= x && x <= TWO_X_POS + TWO_WIDTH && TWO_Y_POS <= y && y <= TWO_Y_POS + TWO_HEIGHT)    
    {
        return TWO;
    }
    else if (THREE_X_POS <= x && x <= THREE_X_POS + THREE_WIDTH && THREE_Y_POS <= y && y <= THREE_Y_POS + THREE_HEIGHT)    
    {
        return THREE;
    }
    else if (MINUS_X_POS <= x && x <= MINUS_X_POS + MINUS_WIDTH && MINUS_Y_POS <= y && y <= MINUS_Y_POS + MINUS_HEIGHT)    
    {
        return MINUS;
    }
    else if (BLUE_SHIFT_X_POS <= x && x <= BLUE_SHIFT_X_POS + BLUE_SHIFT_WIDTH && BLUE_SHIFT_Y_POS <= y && y <= BLUE_SHIFT_Y_POS + BLUE_SHIFT_HEIGHT)    
    {
        return BLUE_SHIFT;
    }
    else if (FOUR_X_POS <= x && x <= FOUR_X_POS + FOUR_WIDTH && FOUR_Y_POS <= y && y <= FOUR_Y_POS + FOUR_HEIGHT)    
    {
        return FOUR;
    }
    else if (FIVE_X_POS <= x && x <= FIVE_X_POS + FIVE_WIDTH && FIVE_Y_POS <= y && y <= FIVE_Y_POS + FIVE_HEIGHT)    
    {
        return FIVE;
    }
    else if (SIX_X_POS <= x && x <= SIX_X_POS + SIX_WIDTH && SIX_Y_POS <= y && y <= SIX_Y_POS + SIX_HEIGHT)    
    {
        return SIX;
    }
    else if (PRODUCT_X_POS <= x && x <= PRODUCT_X_POS + PRODUCT_WIDTH && PRODUCT_Y_POS <= y && y <= PRODUCT_Y_POS + PRODUCT_HEIGHT)    
    {
        return PRODUCT;
    }
    else if (YELLOW_SHIFT_X_POS <= x && x <= YELLOW_SHIFT_X_POS + YELLOW_SHIFT_WIDTH && YELLOW_SHIFT_Y_POS <= y && y <= YELLOW_SHIFT_Y_POS + YELLOW_SHIFT_HEIGHT)    
    {
        return YELLOW_SHIFT;
    }
    else if (SEVEN_X_POS <= x && x <= SEVEN_X_POS + SEVEN_WIDTH && SEVEN_Y_POS <= y && y <= SEVEN_Y_POS + SEVEN_HEIGHT)    
    {
        return SEVEN;
    }
    else if (EIGHT_X_POS <= x && x <= EIGHT_X_POS + EIGHT_WIDTH && EIGHT_Y_POS <= y && y <= EIGHT_Y_POS + EIGHT_HEIGHT)    
    {
        return EIGHT;
    }
    else if (NINE_X_POS <= x && x <= NINE_X_POS + NINE_WIDTH && NINE_Y_POS <= y && y <= NINE_Y_POS + NINE_HEIGHT)    
    {
        return NINE;
    }
    else if (QUOTIENT_X_POS <= x && x <= QUOTIENT_X_POS + QUOTIENT_WIDTH && QUOTIENT_Y_POS <= y && y <= QUOTIENT_Y_POS + QUOTIENT_HEIGHT)    
    {
        return QUOTIENT;
    }
    else if (POWER_TEN_X_POS <= x && x <= POWER_TEN_X_POS + POWER_TEN_WIDTH && POWER_TEN_Y_POS <= y && y <= POWER_TEN_Y_POS + POWER_TEN_HEIGHT)    
    {
        return POWER_TEN;
    }
    else if (PI_X_POS <= x && x <= PI_X_POS + PI_WIDTH && PI_Y_POS <= y && y <= PI_Y_POS + PI_HEIGHT)    
    {
        return PI;
    }
    else if (CHANGE_SIGN_X_POS <= x && x <= CHANGE_SIGN_X_POS + CHANGE_SIGN_WIDTH && CHANGE_SIGN_Y_POS <= y && y <= CHANGE_SIGN_Y_POS + CHANGE_SIGN_HEIGHT)    
    {
        return CHANGE_SIGN;
    }
    else if (LEFT_BRACKET_X_POS <= x && x <= LEFT_BRACKET_X_POS + LEFT_BRACKET_WIDTH && LEFT_BRACKET_Y_POS <= y && y <= LEFT_BRACKET_Y_POS + LEFT_BRACKET_HEIGHT)    
    {
        return LEFT_BRACKET;
    }
    else if (RIGHT_BRACKET_X_POS <= x && x <= RIGHT_BRACKET_X_POS + RIGHT_BRACKET_WIDTH && RIGHT_BRACKET_Y_POS <= y && y <= RIGHT_BRACKET_Y_POS + RIGHT_BRACKET_HEIGHT)    
    {
        return RIGHT_BRACKET;
    }
    else if (LIBRARY_X_POS <= x && x <= LIBRARY_X_POS + LIBRARY_WIDTH && LIBRARY_Y_POS <= y && y <= LIBRARY_Y_POS + LIBRARY_HEIGHT)    
    {
        return LIBRARY;
    }
    else if (SINE_X_POS <= x && x <= SINE_X_POS + SINE_WIDTH && SINE_Y_POS <= y && y <= SINE_Y_POS + SINE_HEIGHT)    
    {
        return SINE;
    }
    else if (COSINE_X_POS <= x && x <= COSINE_X_POS + COSINE_WIDTH && COSINE_Y_POS <= y && y <= COSINE_Y_POS + COSINE_HEIGHT)    
    {
        return COSINE;
    }
    else if (TANGENT_X_POS <= x && x <= TANGENT_X_POS + TANGENT_WIDTH && TANGENT_Y_POS <= y && y <= TANGENT_Y_POS + TANGENT_HEIGHT)    
    {
        return TANGENT;
    }
    else if (FRACTION_X_POS <= x && x <= FRACTION_X_POS + FRACTION_WIDTH && FRACTION_Y_POS <= y && y <= FRACTION_Y_POS + FRACTION_HEIGHT)    
    {
        return FRACTION;
    }
    else if (DOWN_X_POS <= x && x <= DOWN_X_POS + DOWN_WIDTH && DOWN_Y_POS <= y && y <= DOWN_Y_POS + DOWN_HEIGHT)    
    {
        return DOWN;
    }
    else if (BACK_X_POS <= x && x <= BACK_X_POS + BACK_WIDTH && BACK_Y_POS <= y && y <= BACK_Y_POS + BACK_HEIGHT)    
    {
        return BACK;
    }
    else if (SQUARE_ROOT_X_POS <= x && x <= SQUARE_ROOT_X_POS + SQUARE_ROOT_WIDTH && SQUARE_ROOT_Y_POS <= y && y <= SQUARE_ROOT_Y_POS + SQUARE_ROOT_HEIGHT)    
    {
        return SQUARE_ROOT;
    }
    else if (SQUARE_X_POS <= x && x <= SQUARE_X_POS + SQUARE_WIDTH && SQUARE_Y_POS <= y && y <= SQUARE_Y_POS + SQUARE_HEIGHT)    
    {
        return SQUARE;
    }
    else if (LOGARITHM_X_POS <= x && x <= LOGARITHM_X_POS + LOGARITHM_WIDTH && LOGARITHM_Y_POS <= y && y <= LOGARITHM_Y_POS + LOGARITHM_HEIGHT)    
    {
        return LOGARITHM;
    }
    else if (LEFT_X_POS <= x && x <= LEFT_X_POS + LEFT_WIDTH && LEFT_Y_POS <= y && y <= LEFT_Y_POS + LEFT_HEIGHT)    
    {
        return LEFT;
    }
    else if (OK_X_POS <= x && x <= OK_X_POS + OK_WIDTH && OK_Y_POS <= y && y <= OK_Y_POS + OK_HEIGHT)    
    {
        return OK;
    }
    else if (RIGHT_X_POS <= x && x <= RIGHT_X_POS + RIGHT_WIDTH && RIGHT_Y_POS <= y && y <= RIGHT_Y_POS + RIGHT_HEIGHT)    
    {
        return RIGHT;
    }
    else if (HOME_X_POS <= x && x <= HOME_X_POS + HOME_WIDTH && HOME_Y_POS <= y && y <= HOME_Y_POS + HOME_HEIGHT)    
    {
        return HOME;
    }
    else if (TOOLBOX_X_POS <= x && x <= TOOLBOX_X_POS + TOOLBOX_WIDTH && TOOLBOX_Y_POS <= y && y <= TOOLBOX_Y_POS + TOOLBOX_HEIGHT)    
    {
        return TOOLBOX;
    }
    else if (BACKSPACE_X_POS <= x && x <= BACKSPACE_X_POS + BACKSPACE_WIDTH && BACKSPACE_Y_POS <= y && y <= BACKSPACE_Y_POS + BACKSPACE_HEIGHT)    
    {
        return BACKSPACE;
    }
    else if (BACKARROW_X_POS <= x && x <= BACKARROW_X_POS + BACKARROW_WIDTH && BACKARROW_Y_POS <= y && y <= BACKARROW_Y_POS + BACKARROW_HEIGHT)    
    {
        return BACKARROW;
    }
    else if (UP_X_POS <= x && x <= UP_X_POS + UP_WIDTH && UP_Y_POS <= y && y <= UP_Y_POS + UP_HEIGHT)    
    {
        return UP;
    }
    else if (SETTINGS_X_POS <= x && x <= SETTINGS_X_POS + SETTINGS_WIDTH && SETTINGS_Y_POS <= y && y <= SETTINGS_Y_POS + SETTINGS_HEIGHT)    
    {
        return SETTINGS;
    }
    else if (FUNCTION_ONE_X_POS <= x && x <= FUNCTION_ONE_X_POS + FUNCTION_ONE_WIDTH && FUNCTION_ONE_Y_POS <= y && y <= FUNCTION_ONE_Y_POS + FUNCTION_ONE_HEIGHT)    
    {
        return FUNCTION_ONE;
    }
    else if (FUNCTION_TWO_X_POS <= x && x <= FUNCTION_TWO_X_POS + FUNCTION_TWO_WIDTH && FUNCTION_TWO_Y_POS <= y && y <= FUNCTION_TWO_Y_POS + FUNCTION_TWO_HEIGHT)    
    {
        return FUNCTION_TWO;
    }
    else if (FUNCTION_THREE_X_POS <= x && x <= FUNCTION_THREE_X_POS + FUNCTION_THREE_WIDTH && FUNCTION_THREE_Y_POS <= y && y <= FUNCTION_THREE_Y_POS + FUNCTION_THREE_HEIGHT)    
    {
        return FUNCTION_THREE;
    }
    else if (FUNCTION_FOUR_X_POS <= x && x <= FUNCTION_FOUR_X_POS + FUNCTION_FOUR_WIDTH && FUNCTION_FOUR_Y_POS <= y && y <= FUNCTION_FOUR_Y_POS + FUNCTION_FOUR_HEIGHT)    
    {
        return FUNCTION_FOUR;
    }
    else if (FUNCTION_FIVE_X_POS <= x && x <= FUNCTION_FIVE_X_POS + FUNCTION_FIVE_WIDTH && FUNCTION_FIVE_Y_POS <= y && y <= FUNCTION_FIVE_Y_POS + FUNCTION_FIVE_HEIGHT)    
    {
        return FUNCTION_FIVE;
    }
    else if (FUNCTION_SIX_X_POS <= x && x <= FUNCTION_SIX_X_POS + FUNCTION_SIX_WIDTH && FUNCTION_SIX_Y_POS <= y && y <= FUNCTION_SIX_Y_POS + FUNCTION_SIX_HEIGHT)    
    {
        return FUNCTION_SIX;
    }
    
    return UNDEFINED; 
}
