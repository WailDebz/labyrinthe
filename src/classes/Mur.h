#ifndef MUR_H
#define MUR_H

#include "Case.h"
class Mur : public Case {
public:
    char afficher() const override { return '#'; }
    TypeCase getType() const override { return TypeCase::MUR; }
    bool estFranchissable() const override { return false; }
    void appliquerEffet(Aventurier& joueur) override;
};
#endif 