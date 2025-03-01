#ifndef __REGLES_H__
#define __REGLES_H__

#include "jeu_de_dames.h"

/**
 * @brief Structure pour gérer les règles du jeu
 */
typedef struct {
    // Indicateur si la prise est obligatoire
    bool prise_obligatoire;
    // Tableau pour stocker les multiples prises possibles
    Coup *prises_multiples[MAX_PRISES];
    int nb_prises;
} Regles;

/**
 * @brief Initialisation des règles du jeu
 * @param regles Pointeur vers la structure Regles à initialiser
 */
void initialiser_regles(Regles *regles);

/**
 * @brief Vérifie si une prise est obligatoire
 * @param regles Pointeur vers la structure Regles
 * @return true si une prise est obligatoire, false sinon
 */
bool est_prise_obligatoire(const Regles *regles);

/**
 * @brief Vérifie si un coup est une prise
 * @param regles Pointeur vers la structure Regles
 * @param coup Coup à vérifier
 * @return true si le coup est une prise, false sinon
 */
bool est_prise(const Regles *regles, const Coup *coup);

/**
 * @brief Gère les prises multiples
 * @param regles Pointeur vers la structure Regles
 * @param coup Coup actuel
 * @return true si des prises multiples sont possibles, false sinon
 */
bool gérer_prises_multiples(Regles *regles, const Coup *coup);

#endif // __REGLES_H__