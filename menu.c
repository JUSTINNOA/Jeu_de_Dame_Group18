#include "SDL.h"
#include <stdlib.h>
#include <stdio.h>
#include "jeu_de_dames.h"

// Définition des constantes
#define LARGEUR_FENETRE 800
#define HAUTEUR_FENETRE 600
#define NB_OPTIONS_MENU 3
#define NB_OPTIONS_CONFIG 3

typedef struct {
    int taille_damier;
    int couleur_joueur;
    int son_actif;
} Config;

void afficher_menu_principal(SDL_Surface *ecran) {
    // Code pour afficher le menu principal
    SDL_Surface *fond = IMG_Load("images/menu_principal.png");
    SDL_BlitSurface(fond, NULL, ecran, NULL);
    SDL_Flip(ecran);

    // Gestion des événements
    SDL_Event event;
    int option = 0;
    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        option = (option - 1 + NB_OPTIONS_MENU) % NB_OPTIONS_MENU;
                        break;
                    case SDLK_DOWN:
                        option = (option + 1) % NB_OPTIONS_MENU;
                        break;
                    case SDLK_RETURN:
                        switch (option) {
                            case 0:
                                // Lancer le jeu
                                break;
                            case 1:
                                afficher_ecran_configuration(ecran);
                                break;
                            case 2:
                                SDL_Quit();
                                exit(0);
                                break;
                        }
                        return;
                }
            }
        }
    }
}

void afficher_ecran_configuration(SDL_Surface *ecran) {
    // Code pour afficher l'écran de configuration
    SDL_Surface *fond = IMG_Load("images/config.png");
    SDL_BlitSurface(fond, NULL, ecran, NULL);
    SDL_Flip(ecran);

    // Gestion des événements
    SDL_Event event;
    int option = 0;
    while (1) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        option = (option - 1 + NB_OPTIONS_CONFIG) % NB_OPTIONS_CONFIG;
                        break;
                    case SDLK_DOWN:
                        option = (option + 1) % NB_OPTIONS_CONFIG;
                        break;
                    case SDLK_RETURN:
                        // Mettre à jour la configuration selon l'option
                        Config config;
                        switch (option) {
                            case 0:
                                config.taille_damier = 10;
                                break;
                            case 1:
                                config.taille_damier = 8;
                                break;
                            case 2:
                                config.taille_damier = 6;
                                break;
                        }
                        // Sauvegarder la configuration
                        return;
                    case SDLK_ESCAPE:
                        return;
                }
            }
        }
    }
}

int main() {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur d'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!ecran) {
        printf("Erreur de création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    afficher_menu_principal(ecran);

    SDL_Quit();
    return 0;
}