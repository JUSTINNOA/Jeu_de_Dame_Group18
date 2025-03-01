#include "jeu_de_dames.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int ancienne_ligne;
    int ancienne_colonne;
    int nouvelle_ligne;
    int nouvelle_colonne;
    bool capture;
    Piece* piece_capturer;
} Move;

typedef struct {
    Move** moves;
    int size;
    int capacity;
} MoveStack;

void init_move_stack(MoveStack* stack) {
    stack->size = 0;
    stack->capacity = 10;
    stack->moves = malloc(stack->capacity * sizeof(Move*));
}

void save_move(MoveStack* stack, Move* move) {
    if (stack->size >= stack->capacity) {
        stack->capacity *= 2;
        stack->moves = realloc(stack->moves, stack->capacity * sizeof(Move*));
    }
    stack->moves[stack->size++] = move;
}

void free_move_stack(MoveStack* stack) {
    for (int i = 0; i < stack->size; i++) {
        free(stack->moves[i]);
    }
    free(stack->moves);
}

void undo_move(MoveStack* stack, Plateau* plateau) {
    if (stack->size == 0) return;

    Move* last_move = stack->moves[--stack->size];
    
    // Annule le déplacement
    plateau->cases[last_move->nouvelle_ligne][last_move->nouvelle_colonne] = VIDE;
    plateau->cases[last_move->ancienne_ligne][last_move->ancienne_colonne] = last_move->piece;

    // Si c'était une capture, remet la pièce capturée
    if (last_move->capture) {
        plateau->cases[last_move->ancienne_ligne + (last_move->nouvelle_ligne - last_move->ancienne_ligne) / 2][
            last_move->ancienne_colonne + (last_move->nouvelle_colonne - last_move->ancienne_colonne) / 2] = 
            last_move->piece_capturer;
    }

    free(last_move);
}