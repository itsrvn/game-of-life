#include <SDL2/SDL.h>
#include "constants.h"
#include "grid.h"
#include "utils.h"

#undef main

int main(void) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    if (!window) return EXIT_FAILURE;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return EXIT_FAILURE;

    int quit = FALSE;

    const int frameDelay = 1000 / 10;
    Uint32 frameStart;
    int frameTime;

    // initialize grid
    const unsigned int cellSize = 10;
    const unsigned int tilesX = (unsigned int)floor(SCREEN_WIDTH / cellSize);
    const unsigned int tilesY = (unsigned int)floor(SCREEN_HEIGHT / cellSize);

    Grid *grid = grid_new(tilesX, tilesY);
    grid_randomize(grid, 1, CELL_RESET_AMOUNT);

    // texture used for drawing grid cells to the screen
    SDL_Texture *texture =
        SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                          SDL_TEXTUREACCESS_STREAMING, tilesX, tilesY);

    // array of pixels (RGBA values)
    unsigned char *pixels = calloc(tilesX * tilesY * 4, sizeof(unsigned char));

    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (SDL_QUIT == event.type) {
                quit = TRUE;
                break;
            }

            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    quit = 1;
                    break;

                case SDLK_r:
                    grid_reset(grid);
                    grid_randomize(grid, 1, CELL_RESET_AMOUNT);
                    break;
            }
        }

        frameStart = SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // generate a new generation of cells
        int err = grid_update(grid);
        if (err != OK) return EXIT_FAILURE;

        // update the pixels based on cell state
        grid_update_pixels(grid, pixels);

        // limit framerate
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);

        SDL_UpdateTexture(texture, NULL, &pixels[0], tilesX * 4);

        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    // free up used memory before quitting
    free(pixels);
    grid_destroy(grid);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
