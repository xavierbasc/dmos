//
//  fonts.c
//  macOS
//
//  Created by Javier Bascones on 13/11/24.
//

#include "fonts.h"
#include <SDL2/SDL.h>

#define FONT_WIDTH   5
#define FONT_HEIGHT  5

unsigned char fnt5[] = {
    0b00001110, // 0
    0b00010011,
    0b00010101,
    0b00011001,
    0b00001110,

    0b00000100, // 1
    0b00001100,
    0b00000100,
    0b00000100,
    0b00001110,

    0b00001110, // 2
    0b00010001,
    0b00000110,
    0b00001000,
    0b00011111,

    0b00011110, // 3
    0b00000001,
    0b00001110,
    0b00000001,
    0b00011110,

    0b00000010, // 4
    0b00000110,
    0b00001010,
    0b00011111,
    0b00000010,

    0b00011111, // 5
    0b00010000,
    0b00011110,
    0b00000001,
    0b00011110,

    0b00001110, // 6
    0b00010000,
    0b00011110,
    0b00010001,
    0b00001110,

    0b00011111, // 7
    0b00000001,
    0b00000010,
    0b00000100,
    0b00000100,

    0b00001110, // 8
    0b00010001,
    0b00001110,
    0b00010001,
    0b00001110,

    0b00001110, // 9
    0b00010001,
    0b00001111,
    0b00000001,
    0b00001110,

    0b00000000, // :
    0b00000000,
    0b00000100,
    0b00000000,
    0b00000100,

    0b00000000, // ;
    0b00000100,
    0b00000000,
    0b00000100,
    0b00001000,

    0b00000010, // <
    0b00000100,
    0b00001000,
    0b00000100,
    0b00000010,

    0b00000000, // =
    0b00001110,
    0b00000000,
    0b00001110,
    0b00000000,

    0b00001000, // >
    0b00000100,
    0b00000010,
    0b00000100,
    0b00001000,

    0b00001110, // ?
    0b00010001,
    0b00000010,
    0b00000100,
    0b00000100,

    0b00001110, // @
    0b00010001,
    0b00010011,
    0b00010000,
    0b00001110,

    0b00001110,
    0b00010001,
    0b00011111,
    0b00010001,
    0b00010001,

    0b00011110,
    0b00010001,
    0b00011110,
    0b00010001,
    0b00011110,
    
    0b00001110,
    0b00010001,
    0b00010000,
    0b00010001,
    0b00001110
};

// draw character
void draw_character(SDL_Renderer* renderer, unsigned char* character, int x, int y) {
    for (int i = 0; i < FONT_WIDTH; i++) {
        for (int j = 0; j < FONT_WIDTH; j++) {
            if (character[i] & (1 << (5 - 1 - j))) {
                SDL_RenderDrawPoint(renderer, x + j, y + i);
            }
        }
    }
}

// draw text
void draw_text(SDL_Renderer* renderer, const char* text, int x, int y) {
    int offsetX = x;

    for (int i = 0; i < strlen(text); i++) {
        char c = text[i];
        draw_character(renderer, &fnt5[(c - '0') * FONT_HEIGHT], offsetX, y);
        offsetX += 5 + 1;  // Mover la posición para el siguiente carácter
    }
    
}
