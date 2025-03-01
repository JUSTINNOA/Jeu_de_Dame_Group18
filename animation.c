#include "animation.h"
#include "SDL.h"
#include <stdio.h>
#include <stdlib.h>

void init_animation() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        exit(1);
    }
}

void draw_board_with_animation(SDL_Renderer *renderer, int board[8][8], int frame) {
    // Animate the board rendering
    // ...
}

void animate_piece_movement(SDL_Renderer *renderer, int from_x, int from_y, int to_x, int to_y, int piece_color) {
    // Animate piece movement with sliding effect
    // ...
    SDL_Delay(50); // Adjust delay for animation speed
}

void cleanup_animation(SDL_Renderer *renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_Quit(SDL_INIT_VIDEO);
}