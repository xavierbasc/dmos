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
    
    return UNDEFINED; 
}
