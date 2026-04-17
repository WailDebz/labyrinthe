#ifndef TRESOR_H
#define TRESOR_H

#include "Case.h"
#include "../constants.h"

// Trésor — Case contenant un trésor à ramasser. Représentée par '+'.
// Après ramassage, s'affiche comme un passage vide.
class Tresor : public Case {
private:
    int  valeur;    // Points de trésor accordés
    bool ramasse;   // true si le trésor a déjà été collecté

public:
    Tresor();

    char afficher() const override;
    TypeCase getType() const override { return TypeCase::TRESOR; }
    bool estFranchissable() const override { return true; }
    void appliquerEffet(Aventurier& joueur) override;
};

#endif // TRESOR_H
