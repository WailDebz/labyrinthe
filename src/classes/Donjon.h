#ifndef DONJON_H
#define DONJON_H

#include <vector>
#include <utility>
#include "Case.h"

// Déclaration anticipée
class Aventurier;

// Donjon — Grille 2D de cases constituant le labyrinthe.
// Responsable de la génération (Recursive Backtracking), du placement
// des éléments, du rendu ASCII et du pathfinding (BFS).
class Donjon {
private:
    std::vector<std::vector<Case*>> grille;
    int largeur;
    int hauteur;
    std::pair<int, int> entree;
    std::pair<int, int> sortie;

    // --- Méthodes privées de génération ---
    void genererLabyrinthe(int x, int y);
    void placerElements();

public:
    Donjon();
    ~Donjon();

    // Génère un donjon de dimensions largeur × hauteur
    void generer(int largeur, int hauteur);

    // --- Affichage ---
    void afficher() const;
    void afficher(const Aventurier& joueur) const;
    void afficherChemin(const Aventurier& joueur,
                        const std::vector<std::pair<int, int>>& chemin) const;

    // --- Pathfinding (BFS) ---
    std::vector<std::pair<int, int>> trouverChemin(
        std::pair<int, int> depart,
        std::pair<int, int> arrivee) const;

    // --- Accesseurs ---
    Case* getCase(int x, int y) const;
    void  setCase(int x, int y, Case* c);
    bool  estDansBornes(int x, int y) const;
    std::pair<int, int> getEntree() const { return entree; }
    std::pair<int, int> getSortie() const { return sortie; }
    int getLargeur() const { return largeur; }
    int getHauteur() const { return hauteur; }
};

#endif // DONJON_H
