#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include "dm50_skin.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
#define SCREEN_WIDTH     70
#define SCREEN_HEIGHT   150

SDL_Texture* load_png_from_memory(const unsigned char* data, int size, SDL_Renderer* renderer) {
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

SDL_Texture* load_png(const char* filename, SDL_Renderer* renderer) {
    int width, height, channels;
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 0);
    if (data == NULL) {
        fprintf(stderr, "Error loading PNG image: %s\n", filename);
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

    // Obtén el tamaño de la pantalla
    SDL_DisplayMode displayMode;
    if (SDL_GetCurrentDisplayMode(0, &displayMode) != 0) {
        fprintf(stderr, "Error getting display mode: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    int screenWidth = displayMode.w;
    int screenHeight = displayMode.h;

    // Calcula la escala máxima manteniendo la proporción 50x170
    int scaleX = screenWidth * 0.80 / SCREEN_WIDTH;
    int scaleY = screenHeight * 0.80 / SCREEN_HEIGHT;
    int scale = (scaleX < scaleY) ? scaleX : scaleY;

    // Asegura una escala mínima de 1 para evitar problemas
    if (scale < 1) scale = 1;

    // Define el tamaño de la ventana escalada
    int windowWidth = SCREEN_WIDTH * scale;
    int windowHeight = SCREEN_HEIGHT * scale;

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if(!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
    {
        printf("SDL can not disable compositor bypass!\n");
        return 0;
    }
#endif

    // Create window
    SDL_Window *window = SDL_CreateWindow("DM50 Calculator",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          windowWidth, windowHeight,
                                          SDL_WINDOW_SHOWN);
    if(!window)
    {
        printf("Window could not be created!\n"
               "SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create renderer
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_RenderSetLogicalSize(renderer, 70, 150);
        SDL_RenderSetIntegerScale(renderer, SDL_TRUE);

        /*
        SDL_Texture* texture = load_png("assets/dm50_skin.png", renderer);
        if (!texture) {
            fprintf(stderr, "Error al cargar la textura PNG.\n");
            SDL_DestroyRenderer(renderer);
            SDL_DestroyWindow(window);
            SDL_Quit();
            return -1;
        }
        */

        SDL_Texture* texture = load_png_from_memory(dm50_skin_png, dm50_skin_png_len, renderer);
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
            // Declare rect of square
            SDL_Rect squareRect;

            // Square dimensions: Half of the min(SCREEN_WIDTH, SCREEN_HEIGHT)
            squareRect.w = 30;
            squareRect.h = 30;

            // Square position: In the middle of the screen
            squareRect.x = 50;
            squareRect.y = 50;


            // Event loop exit flag
            bool quit = false;

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

                // Initialize renderer color white for the background
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                // Clear screen
                SDL_RenderClear(renderer);

                // Set renderer color red to draw the square
                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);

                // Draw filled square
                SDL_RenderFillRect(renderer, &squareRect);

                SDL_RenderCopy(renderer, texture, NULL, NULL);
                
                // Update screen
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
