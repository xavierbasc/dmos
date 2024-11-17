//
//  fonts.c
//  macOS
//
//  Created by Javier Bascones on 13/11/24.
//

#include "fonts.h"
#include "SDL.h"

#define FONT_WIDTH   5
#define FONT_HEIGHT  5

unsigned char fnt5[] = {
    0b00000000, // (space)
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    
    0b00000100, // !
    0b00000100,
    0b00000000,
    0b00000100,
    0b00000100,
    
    0b00001010, // "
    0b00001010,
    0b00000000,
    0b00000000,
    0b00000000,
    
    0b00001010, // #
    0b00011011,
    0b00001010,
    0b00011011,
    0b00001010,
    
    0b00001111, // $
    0b00010100,
    0b00001110,
    0b00000101,
    0b00011110,
    
    0b00000000, // %
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    
    0b00000000, // &
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    
    0b00000000, // '
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    
    0b00000000, // (
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    
    0b00000000, // )
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    
    0b00000000, // *
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    
    0b00000000, // +
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    
    0b00000000, // ,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    
    0b00000000, // -
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    
    0b00000000, // .
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    
    0b00000000, // /
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    
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
    
    0b00001110, // A
    0b00010001,
    0b00011111,
    0b00010001,
    0b00010001,
    
    0b00011110, // B
    0b00010001,
    0b00011110,
    0b00010001,
    0b00011110,
    
    0b00001110, // C
    0b00010001,
    0b00010000,
    0b00010001,
    0b00001110,

    0b00000000, // D
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // E
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // F
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // G
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00010001, // H
    0b00010001,
    0b00011111,
    0b00010001,
    0b00010001,

    0b00000000, // I
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // J
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // K
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // L
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // M
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // N
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // O
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // P
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // Q
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // R
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // S
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // T
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // U
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // V
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00010101, // W
    0b00010101,
    0b00010101,
    0b00010101,
    0b00001010,

    0b00000000, // X
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // Y
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00011111, // Z
    0b00000010,
    0b00000100,
    0b00001000,
    0b00011111,

    0b00000000, // [
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // (backslash)
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // ]
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // ^
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // _
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // '
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // a
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // b
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // c
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000001, // d
    0b00000001,
    0b00001111,
    0b00010001,
    0b00001111,

    0b00001110, // e
    0b00010001,
    0b00011111,
    0b00010000,
    0b00001111,

    0b00000000, // f
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // g
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // h
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // i
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // j
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // k
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00001100, // l
    0b00000100,
    0b00000100,
    0b00000100,
    0b00001110,

    0b00000000, // m
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // n
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // o
    0b00001110,
    0b00010001,
    0b00010001,
    0b00001110,

    0b00000000, // p
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // q
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // r
    0b00010111,
    0b00011000,
    0b00010000,
    0b00010000,

    0b00000000, // s
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // t
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // u
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // v
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // w
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // x
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // y
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, // z
    0b00011111,
    0b00000010,
    0b00001100,
    0b00011111,

    0b00000000, //
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, //
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, //
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,

    0b00000000, //
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000

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
        draw_character(renderer, &fnt5[(c - ' ') * FONT_HEIGHT], offsetX, y);
        offsetX += 5 + 1;  // Mover la posición para el siguiente carácter
    }
    
}
