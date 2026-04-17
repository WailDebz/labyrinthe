#include "CaseFactory.h"
#include "Mur.h"
#include "Passage.h"
#include "Tresor.h"
#include "Monstre.h"
#include "Piege.h"

// Seul endroit du code qui inclut les en-têtes des sous-classes concrètes.
Case* CaseFactory::creerCase(TypeCase type) {
    switch (type) {
        case TypeCase::MUR:
            return new Mur();
        case TypeCase::PASSAGE:
            return new Passage();
        case TypeCase::TRESOR:
            return new Tresor();
        case TypeCase::MONSTRE:
            return new Monstre();
        case TypeCase::PIEGE:
            return new Piege();
        default:
            return new Mur();   // Défaut défensif
    }
}
