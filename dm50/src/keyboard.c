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
    
    return UNDEFINED; 
}
