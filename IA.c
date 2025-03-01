#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jeu_de_dames.h"

// Structure pour définir les niveaux de difficulté
typedef struct {
    int niveau;
    int profondeur;
} NiveauDifficulte;

// Variable globale pour stocker le niveau de difficulté actuel
NiveauDifficulte niveauActuel = {0, 0};

// Fonction pour définir le niveau de difficulté
void setNiveauDifficulte(int niveau) {
    switch(niveau) {
        case 1:
            niveauActuel.niveau = 1;
            niveauActuel.profondateur = 1;
            break;
        case 2:
            niveauActuel.niveau = 2;
            niveauActuel.profondateur = 3;
            break;
        case 3:
            niveauActuel.niveau = 3;
            niveauActuel.profondateur = 5;
            break;
        default:
            niveauActuel.niveau = 1;
            niveauActuel.profondateur = 1;
            break;
    }
}

// Fonction pour obtenir le niveau de difficulté actuel
int getNiveauDifficulte() {
    return niveauActuel.niveau;
}

// Fonction pour obtenir la profondeur de recherche actuelle
int getProfondateurRecherche() {
    return niveauActuel.profondateur;
}

// Fonction pour initialiser l'IA
void initialiserIA() {
    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires
}

// Fonction pour évaluer la qualité d'une position (heuristique)
int evaluationPosition(Plateau *plateau) {
    int score = 0;
    // Évaluez la position en fonction des pièces et de leur position
    // Par exemple, plus de pièces proches de la promotion donnent un meilleur score
    return score;
}

// Fonction pour générer tous les coups possibles
ListeCoups *genererCoupsPossibles(Plateau *plateau, Joueur *joueur) {
    // Générez tous les coups possibles pour le joueur actuel
    // Cette fonction doit être implémentée selon les règles du jeu
    return NULL;
}

// Fonction pour évaluer le meilleur coup à jouer
Coup *meilleurCoup(Plateau *plateau, Joueur *joueur) {
    // Implémentez l'algorithme Minimax avec élagage alpha-bêta
    // Selon le niveau de difficulté, ajustez la profondeur de recherche
    int profondeur = getProfondateurRecherche();
    int meilleurScore = -INFINI;
    ListeCoups *coups = genererCoupsPossibles(plateau, joueur);
    Coup *meilleurCoup = NULL;

    for (Coup *coup = coups->premier; coup != NULL; coup = coup->suivant) {
        // Simulez le coup
        Plateau *copiePlateau = copierPlateau(plateau);
        jouerCoup(copiePlateau, coup);
        
        // Évaluez la position après le coup
        int score = minimax(copiePlateau, getProfondateurRecherche(), -INFINI, INFINI, !joueur->estBlanc);

        if (score > meilleurScore) {
            meilleurScore = score;
            meilleurCoup = coup;
        }
    }

    return meilleurCoup;
}

// Fonction Minimax avec élagage alpha-bêta
int minimax(Plateau *plateau, int profondeur, int alpha, int beta, bool estIA) {
    if (profondeur == 0 || partieTerminee(plateau)) {
        return evaluationPosition(plateau);
    }

    if (estIA) {
        int maxScore = -INFINI;
        ListeCoups *coups = genererCoupsPossibles(plateau, &joueurIA);
        for (Coup *coup = coups->premier; coup != NULL; coup = coup->suivant) {
            Plateau *copiePlateau = copierPlateau(plateau);
            jouerCoup(copiePlateau, coup);
            int score = minimax(copiePlateau, profondeur - 1, alpha, beta, false);
            maxScore = max(maxScore, score);
            alpha = max(alpha, score);
            if (alpha >= beta) {
                break;
            }
        }
        return maxScore;
    } else {
        int minScore = INFINI;
        ListeCoups *coups = genererCoupsPossibles(plateau, &joueurHumain);
        for (Coup *coup = coups->premier; coup != NULL; coup = coup->suivant) {
            Plateau *copiePlateau = copierPlateau(plateau);
            jouerCoup(copiePlateau, coup);
            int score = minimax(copiePlateau, profondeur - 1, alpha, beta, true);
            minScore = min(minScore, score);
            beta = min(beta, score);
            if (alpha >= beta) {
                break;
            }
        }
        return minScore;
    }
}

// Fonction pour obtenir un coup aléatoire (pour le niveau facile)
Coup *coupAleatoire(Plateau *plateau, Joueur *joueur) {
    ListeCoups *coups = genererCoupsPossibles(plateau, joueur);
    if (coups == NULL || coups->premier == NULL) {
        return NULL;
    }
    int nombreCoups = 0;
    for (Coup *coup = coups->premier; coup != NULL; coup = coup->suivant) {
        nombreCoups++;
    }
    int index = rand() % nombreCoups;
    Coup *coup = coups->premier;
    for (int i = 0; i < index; i++) {
        coup = coup->suivant;
    }
    return coup;
}

// Fonction principale de l'IA
Coup *calculerCoupIA(Plateau *plateau, Joueur *joueur) {
    switch(getNiveauDifficulte()) {
        case 1: // Facile
            return coupAleatoire(plateau, joueur);
        case 2: // Moyen
        case 3: // Difficile
            return meilleurCoup(plateau, joueur);
        default:
            return NULL;
    }
}