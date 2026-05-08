#ifndef CASE_H
#define CASE_H

#include <iostream>
#include "../TypeCase.h"

// Déclaration anticipée pour éviter les inclusions circulaires
class Aventurier;

// Classe abstraite de base représentant une case du donjon.
// Toutes les sous-classes concrètes (Mur, Passage, Tresor, Monstre, Piege)
// doivent implémenter les méthodes virtuelles pures.
class Case {
public:
    // Retourne le caractère ASCII représentant cette case
    virtual char afficher() const = 0;

    // Retourne le type énuméré de cette case
    virtual TypeCase getType() const = 0;

    // Retourne true si l'aventurier peut marcher sur cette case
    virtual bool estFranchissable() const = 0;

    // Applique l'effet de la case sur l'aventurier (trésor, piège, monstre...)
    virtual void appliquerEffet(Aventurier& joueur) = 0;

    // Destructeur virtuel pour suppression polymorphe correcte
    virtual ~Case() = default;

    // Surcharge de l'opérateur << pour affichage
    friend std::ostream& operator<<(std::ostream& os, const Case& c) {
        os << c.afficher();
        return os;
    }
};

#endif // CASE_H
