#ifndef CASE_H
#define CASE_H

#include <iostream>
#include "../TypeCase.h"
class Aventurier;
class Case {
public:
    virtual char afficher() const = 0;
    virtual TypeCase getType() const = 0;
    virtual bool estFranchissable() const = 0;
    virtual void appliquerEffet(Aventurier& joueur) = 0;
    virtual ~Case() = default;
    friend std::ostream& operator<<(std::ostream& os, const Case& c) {
        os << c.afficher();
        return os;
    }
};
#endif // CASE_H
