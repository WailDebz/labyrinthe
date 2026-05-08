#ifndef DONJON_H
#define DONJON_H
#include <vector>
#include <utility>
#include "Case.h"
class Aventurier;
class Donjon {
private:
    std::vector<std::vector<Case*>> grille;
    int largeur;
    int hauteur;
    std::pair<int, int> entree;
    std::pair<int, int> sortie;
    void genererLabyrinthe(int x, int y);
    void placerElements();
public:
    Donjon();
    ~Donjon();
    void generer(int largeur, int hauteur);
    void afficher() const;
    void afficher(const Aventurier& joueur) const;
    void afficherChemin(const Aventurier& joueur,
                        const std::vector<std::pair<int, int>>& chemin) const;
    std::vector<std::pair<int, int>> trouverChemin(
        std::pair<int, int> depart,
        std::pair<int, int> arrivee) const;
    Case* getCase(int x, int y) const;
    void  setCase(int x, int y, Case* c);
    bool  estDansBornes(int x, int y) const;
    std::pair<int, int> getEntree() const { return entree; }
    std::pair<int, int> getSortie() const { return sortie; }
    int getLargeur() const { return largeur; }
    int getHauteur() const { return hauteur; }
};
#endif 