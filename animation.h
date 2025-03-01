#ifndef ANIMATION_H
#define ANIMATION_H

#include "SDL.h"

void init_animation();
void draw_board_with_animation(SDL_Renderer *renderer, int board[8][8], int frame);
void animate_piece_movement(SDL_Renderer *renderer, int from_x, int from_y, int to_x, int to_y, int piece_color);
void cleanup_animation(SDL_Renderer *renderer);

#endif // ANIMATION_H