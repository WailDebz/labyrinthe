#ifndef MONSTRE_H
#define MONSTRE_H

#include "Case.h"
#include "../constants.h"
#include <string>

// Monstre — Case contenant un monstre. Représentée par 'M'.
// Le joueur peut choisir de combattre ou de fuir.
// Une fois vaincu, le monstre disparaît (affichage passage).
class Monstre : public Case {
private:
    std::string nom;       // Nom du monstre
    int         degats;    // Dégâts infligés au joueur lors du combat
    bool        vaincu;    // true si le monstre a été vaincu

public:
    Monstre();
    Monstre(const std::string& nom, int degats);

    char afficher() const override;
    TypeCase getType() const override { return TypeCase::MONSTRE; }
    bool estFranchissable() const override { return true; }
    void appliquerEffet(Aventurier& joueur) override;

    const std::string& getNom() const { return nom; }
    int getDegats() const { return degats; }
    bool estVaincu() const { return vaincu; }
};

#endif // MONSTRE_H
