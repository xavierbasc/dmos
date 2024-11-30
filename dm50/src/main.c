#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "SDL.h"
#include "dm50_skin.h"
#include "fonts.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
#define SCREEN_WIDTH   130 //70
#define SCREEN_HEIGHT  278 //150

SDL_Texture* load_img_from_memory(const unsigned char* data, int size, SDL_Renderer* renderer) {
    int width, height, channels;
    
    // Cargar la imagen desde la memoria con stb_image
    unsigned char* img_data = stbi_load_from_memory(data, size, &width, &height, &channels, STBI_rgb_alpha);  // Se asegura de usar RGBA
    if (img_data == NULL) {
        fprintf(stderr, "Error loading image from memory: %s\n", stbi_failure_reason());
        return NULL;
    }

    // Crear la superficie SDL2 desde los datos de la imagen cargada
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(
        img_data, width, height, 32, width * 4, SDL_PIXELFORMAT_RGBA32);
    if (!surface) {
        fprintf(stderr, "Error creating SDL surface: %s\n", SDL_GetError());
        stbi_image_free(img_data);
        return NULL;
    }

    // Crear la textura a partir de la superficie
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    stbi_image_free(img_data);  // Liberar los datos de la imagen cargada

    return texture;
}

SDL_Texture* load_img(const char* filename, SDL_Renderer* renderer) {
    int width, height, channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 0);
    if (data == NULL) {
        fprintf(stderr, "Error loading image: %s\n", filename);
        return NULL;
    }

    // Crear una superficie SDL2 a partir de los datos de la imagen
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(
        data, width, height, 32, width * 4, SDL_PIXELFORMAT_RGBA32);
    if (!surface) {
        fprintf(stderr, "Error creating SDL2 surface.\n");
        stbi_image_free(data);
        return NULL;
    }

    // Crear una textura a partir de la superficie
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    stbi_image_free(data);  // Liberar la memoria de la imagen cargada

    return texture;
}

int main(int argc, char* argv[])
{
    // Unused argc, argv
    (void) argc;
    (void) argv;

    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not be initialized!\n"
               "SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    
    int screenWidth;
    int screenHeight;
    int windowWidth;
    int windowHeight;

    int scaleX, scaleY;
    
    if (strcmp(SDL_GetPlatform(), "iOS") == 0) {
        scaleX = screenWidth / SCREEN_WIDTH;
        scaleY = screenHeight / SCREEN_HEIGHT;
    } else {
        // Obtén el tamaño de la pantalla
        SDL_DisplayMode displayMode;
        if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
            fprintf(stderr, "Error getting display mode: %s\n", SDL_GetError());
            SDL_Quit();
            return 1;
        }
        screenWidth = displayMode.w;
        screenHeight = displayMode.h;
        
        // Calcula la escala máxima manteniendo la proporción 50x170
        scaleX = screenWidth * 0.80 / SCREEN_WIDTH;
        scaleY = screenHeight * 0.80 / SCREEN_HEIGHT;
    }

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if(!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
    {
        printf("SDL can not disable compositor bypass!\n");
        return 0;
    }
#endif
    SDL_Window *window;

    if (strcmp(SDL_GetPlatform(), "iOS") == 0) {
        window = SDL_CreateWindow(NULL,
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            0, 0, SDL_WINDOW_FULLSCREEN|SDL_WINDOW_ALLOW_HIGHDPI
        );
    } else {
        int scale = (scaleX < scaleY) ? scaleX : scaleY;

        // Asegura una escala mínima de 1 para evitar problemas
        if (scale < 1) scale = 1;

        // Define el tamaño de la ventana escalada
        windowWidth = SCREEN_WIDTH * scale;
        windowHeight = SCREEN_HEIGHT * scale;

        window = SDL_CreateWindow("DM50",
              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
              windowWidth, windowHeight,
              SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    }
    
    
    if(!window)
    {
        printf("Window could not be created!\n"
               "SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        SDL_GetWindowSize(window, &screenWidth, &screenHeight);
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        
        if (strcmp(SDL_GetPlatform(), "iOS") == 0) {
            //SDL_RenderSetLogicalSize(renderer, screenWidth, screenHeight);
            SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);
           // SDL_RenderSetIntegerScale(renderer, SDL_TRUE);

            // PIXEL PERFECT
            SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
            scaleX = screenWidth / SCREEN_WIDTH;
            scaleY = screenHeight /SCREEN_HEIGHT;
            SDL_RenderSetScale(renderer, scaleX, scaleX);
            SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH*scaleX, SCREEN_HEIGHT*scaleX);

        } else {
            SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
            SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
        }


        
        
        SDL_Texture* texture = load_img_from_memory(dm50_skin_gif, dm50_skin_gif_len, renderer);

        if (!texture) {
            fprintf(stderr, "Error loading PNG texture from memory.\n");
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return -1;
        }

        
        if(!renderer)
        {
            printf("Renderer could not be created!\n"
                   "SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            // Event loop exit flag
            bool quit = false;

            int width, height;
            SDL_GetRendererOutputSize(renderer, &width, &height);
            
            // Event loop
            while(!quit)
            {
                SDL_Event e;

                // Wait indefinitely for the next available event
                SDL_WaitEvent(&e);

                // User requests quit
                if(e.type == SDL_QUIT)
                {
                    quit = true;
                }

                
                //SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF); // White
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); // White
                SDL_RenderClear(renderer); // Clear screen

                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF); // Red
                SDL_RenderCopy(renderer, texture, NULL, NULL);
                
                /*
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0xFF);
                SDL_Rect rect2 = {1, 1, screenWidth, screenHeight};
                SDL_RenderFillRect(renderer, &rect2);
                */

                // LCD
                SDL_SetRenderDrawColor(renderer, 196, 191, 185, 0xFF);
                SDL_Rect rect = {1, 1, 128, 64};
                SDL_RenderFillRect(renderer, &rect);

                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF); // White
                draw_text(renderer, ">01234567890123456789", 1, 1);
                draw_text(renderer, ">ABCZabcz", 1, 7);
                draw_text(renderer, "Hello World", 25, 30);

                //SDL_RenderDrawPoint(renderer, 0, 30);
                //SDL_RenderDrawPoint(renderer, SCREEN_WIDTH-1, 30);

                // Draw text
                SDL_RenderPresent(renderer);
            }

            // Destroy renderer
            SDL_DestroyTexture(texture);
            SDL_DestroyRenderer(renderer);
        }

        // Destroy window
        SDL_DestroyWindow(window);
    }

    // Quit SDL
    SDL_Quit();

    return 0;
}
