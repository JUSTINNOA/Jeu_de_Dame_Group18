#include "SDL.h"
#include "gestion_sonore.h"

void initialiser_son() {
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Erreur initialisation audio : %s\n", Mix_GetError());
    }
}

void charger_son() {
    // Chargement des sons ici
    // Exemple :
    // son_mouvement = Mix_LoadWAV("mouvement.wav");
    // son_capture = Mix_LoadWAV("capture.wav");
}

void joue_son(int son) {
    Mix_PlayChannel(-1, son, 0);
}

void liberer_ressources() {
    Mix_CloseAudio();
}