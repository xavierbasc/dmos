//
//  fonts.h
//  macOS
//
//  Created by Javier Bascones on 13/11/24.
//

#ifndef FONTS_H
#define FONTS_H

#include "SDL.h"

void initFonts(void);
void draw_character(SDL_Renderer* renderer, unsigned char* character, int x, int y);
void draw_text(SDL_Renderer* renderer, const char* text, int x, int y);

#endif  // FONT_H
