#ifndef CONSTANTS_H
#define CONSTANTS_H

// --- Dimensions par défaut du donjon ---
constexpr int LARGEUR_DEFAULT = 21;   // Doit être impair pour l'algorithme de génération
constexpr int HAUTEUR_DEFAULT = 21;

// --- Statistiques de l'aventurier ---
constexpr int SANTE_MAX = 100;

// --- Dégâts ---
constexpr int DEGATS_MONSTRE = 15;
constexpr int DEGATS_PIEGE   = 20;

// --- Trésors ---
constexpr int VALEUR_TRESOR = 1;

// --- Probabilités de placement (seuils cumulatifs sur 100) ---
constexpr int PROB_TRESOR  = 5;    // 0..4   → trésor   (5%)
constexpr int PROB_MONSTRE = 10;   // 5..9   → monstre  (5%)
constexpr int PROB_PIEGE   = 13;   // 10..12 → piège    (3%)

#endif // CONSTANTS_H
