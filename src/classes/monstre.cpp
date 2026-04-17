#include "Monstre.h"
#include "Aventurier.h"
#include <iostream>

Monstre::Monstre() : nom("Goblin"), degats(DEGATS_MONSTRE), vaincu(false) {}

Monstre::Monstre(const std::string& nom, int degats)
    : nom(nom), degats(degats), vaincu(false) {}

char Monstre::afficher() const {
    return vaincu ? ' ' : 'M';
}

void Monstre::appliquerEffet(Aventurier& joueur) {
    if (vaincu) return;

    std::cout << "\n  !! Un " << nom << " vous barre la route !\n";
    std::cout << "  [C] Combattre  [F] Fuir\n";
    std::cout << "  > ";

    char choix;
    std::cin >> choix;

    if (choix == 'C' || choix == 'c') {
        joueur.recevoirDegats(degats);
        vaincu = true;
        std::cout << "  Vous terrassez le " << nom << " ! (-" << degats << " HP)\n";
    } else {
        // Fuite — le joueur retourne à sa position précédente
        auto prev = joueur.getPositionPrecedente();
        joueur.deplacer(prev.first, prev.second);
        std::cout << "  Vous fuyez le combat !\n";
    }
}
