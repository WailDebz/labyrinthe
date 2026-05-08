#ifndef PASSAGE_H
#define PASSAGE_H

#include "Case.h"
class Passage : public Case {
public:
    char afficher() const override { return ' '; }
    TypeCase getType() const override { return TypeCase::PASSAGE; }
    bool estFranchissable() const override { return true; }
    void appliquerEffet(Aventurier& joueur) override;
};

#endif 