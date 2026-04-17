#include "Tresor.h"
#include "Aventurier.h"
#include <iostream>

Tresor::Tresor() : valeur(VALEUR_TRESOR), ramasse(false) {}

char Tresor::afficher() const {
    return ramasse ? ' ' : '+';
}

void Tresor::appliquerEffet(Aventurier& joueur) {
    if (!ramasse) {
        joueur.ajouterTresor(valeur);
        ramasse = true;
        std::cout << "  Vous avez trouve un tresor ! (+" << valeur << ")\n";
    }
}
