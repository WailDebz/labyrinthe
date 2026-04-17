#include "Piege.h"
#include "Aventurier.h"
#include <iostream>

Piege::Piege() : degats(DEGATS_PIEGE), active(true) {}

char Piege::afficher() const {
    return active ? 'T' : ' ';
}

void Piege::appliquerEffet(Aventurier& joueur) {
    if (active) {
        joueur.recevoirDegats(degats);
        active = false;
        std::cout << "  Vous declenchez un piege ! (-" << degats << " HP)\n";
    }
}
