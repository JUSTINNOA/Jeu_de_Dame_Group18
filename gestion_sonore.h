#ifndef GESTION_SONORE_H
#define GESTION_SONORE_H

#include "SDL.h"

void initialiser_son(void);
void charger_son(void);
void joue_son(int son);
void liberer_ressources(void);

#endif  // GESTION_SONORE_H