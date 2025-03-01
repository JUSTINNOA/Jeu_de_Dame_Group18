#include <stdio.h>
#include <stdlib.h>
#include "jeu_de_dames.h"

#define SAUVEGARDE_VERSION 1
#define SAUVEGARDE_HEADER "JEU_DE_DAME_SAUV"

int sauvegarder_partie(const char *nom_fichier, const struct_partie *partie) {
    FILE *fichier = fopen(nom_fichier, "wb");
    if (fichier == NULL) {
        return 0;
    }

    // Écrire l'entête de sauvegarde
    fwrite(SAUVEGARDE_HEADER, sizeof(char), strlen(SAUVEGARDE_HEADER), fichier);
    fputc('\n', fichier);
    fwrite(&SAUVEGARDE_VERSION, sizeof(int), 1, fichier);
    fputc('\n', fichier);

    // Écrire l'état de la partie
    fwrite(&partie->joueur_actuel, sizeof(int), 1, fichier);
    fputc('\n', fichier);
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (partie->board[i][j].piece.type != VIDE) {
                // Sauvegarder le type et la position de la pièce
                fwrite(&partie->board[i][j].piece.type, sizeof(int), 1, fichier);
                fputc('\n', fichier);
                fwrite(&i, sizeof(int), 1, fichier);
                fputc('\n', fichier);
                fwrite(&j, sizeof(int), 1, fichier);
                fputc('\n', fichier);
            }
        }
    }

    fclose(fichier);
    return 1;
}

int charger_partie(const char *nom_fichier, struct_partie *partie) {
    FILE *fichier = fopen(nom_fichier, "rb");
    if (fichier == NULL) {
        return 0;
    }

    char header[256];
    int version;
    int type_piece;
    int x, y;

    // Lire l'entête de sauvegarde
    fgets(header, sizeof(header), fichier);
    if (strcmp(header, SAUVEGARDE_HEADER "\n") != 0) {
        fclose(fichier);
        return 0;
    }

    fread(&version, sizeof(int), 1, fichier);
    if (version != SAUVEGARDE_VERSION) {
        fclose(fichier);
        return 0;
    }

    // Initialiser la partie
    initialiser_partie(partie);

    // Lire les pièces
    while (!feof(fichier)) {
        fread(&type_piece, sizeof(int), 1, fichier);
        if (ferror(fichier)) break;

        fread(&x, sizeof(int), 1, fichier);
        fread(&y, sizeof(int), 1, fichier);

        if (x >= 0 && x < 10 && y >= 0 && y < 10) {
            partie->board[x][y].piece.type = type_piece;
        }
    }

    fclose(fichier);
    return 1;
}