#ifndef PASSAGE_H
#define PASSAGE_H

#include "Case.h"

// Passage — Couloir vide et franchissable. Représenté par ' '.
class Passage : public Case {
public:
    char afficher() const override { return ' '; }
    TypeCase getType() const override { return TypeCase::PASSAGE; }
    bool estFranchissable() const override { return true; }
    void appliquerEffet(Aventurier& joueur) override;
};

#endif // PASSAGE_H
