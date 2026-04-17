#ifndef AVENTURIER_H
#define AVENTURIER_H

#include <iostream>
#include <utility>

// Déclaration anticipée
class Donjon;
class Case;

// Aventurier — Le joueur explorant le donjon.
// Encapsule la position, les points de vie et l'inventaire.
class Aventurier {
private:
    int posX;         // Position courante — colonne
    int posY;         // Position courante — ligne
    int prevX;        // Position précédente — colonne (pour la fuite)
    int prevY;        // Position précédente — ligne
    int sante;        // Points de vie
    int inventaire;   // Nombre de trésors collectés

public:
    // Constructeur : place l'aventurier à la position de départ
    Aventurier(int startX, int startY);

    // --- Déplacements ---
    // Met à jour la position. Précondition : la case cible est franchissable.
    void deplacer(int nx, int ny);

    // --- Interactions ---
    // Applique l'effet de la case via dispatch polymorphe
    void resoudreCase(Case* c);

    // --- Gestion de l'état ---
    bool estVivant() const;
    void recevoirDegats(int dmg);
    void ajouterTresor(int val);

    // --- Accesseurs ---
    std::pair<int, int> getPosition() const;
    std::pair<int, int> getPositionPrecedente() const;
    int getSante() const { return sante; }
    int getInventaire() const { return inventaire; }

    // --- Affichage ---
    void afficherStatut() const;

    // --- Boucle de jeu principale ---
    void boucleDeJeu(Donjon& d);

    // Surcharge de l'opérateur <<
    friend std::ostream& operator<<(std::ostream& os, const Aventurier& a);
};

#endif // AVENTURIER_H
