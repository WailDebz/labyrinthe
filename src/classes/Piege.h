#ifndef PIEGE_H
#define PIEGE_H

#include "Case.h"
#include "../constants.h"

// Piège — Case infligeant des dégâts automatiques. Représentée par 'T'.
// Se désactive après le premier déclenchement.
class Piege : public Case {
private:
    int  degats;   // Dégâts infligés
    bool active;   // true si le piège est encore armé

public:
    Piege();

    char afficher() const override;
    TypeCase getType() const override { return TypeCase::PIEGE; }
    bool estFranchissable() const override { return true; }
    void appliquerEffet(Aventurier& joueur) override;
};

#endif // PIEGE_H
