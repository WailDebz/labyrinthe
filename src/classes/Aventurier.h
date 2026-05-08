#ifndef AVENTURIER_H
#define AVENTURIER_H
#include <iostream>
#include <utility>
class Donjon;
class Case;
class Aventurier {
private:
    int posX;         // Position courante — colonne
    int posY;         // Position courante — ligne
    int prevX;        // Position précédente — colonne (pour la fuite)
    int prevY;        // Position précédente — ligne
    int sante;        // Points de vie
    int inventaire;   // Nombre de trésors collectés
public:
    Aventurier(int startX, int startY);
    void deplacer(int nx, int ny);
    void resoudreCase(Case* c);
    bool estVivant() const;
    void recevoirDegats(int dmg);
    void ajouterTresor(int val);
    std::pair<int, int> getPosition() const;
    std::pair<int, int> getPositionPrecedente() const;
    int getSante() const { return sante; }
    int getInventaire() const { return inventaire; }
    void afficherStatut() const;
    void boucleDeJeu(Donjon& d);
    friend std::ostream& operator<<(std::ostream& os, const Aventurier& a);
};
#endif 