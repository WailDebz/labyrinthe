#ifndef CASEFACTORY_H
#define CASEFACTORY_H

#include "Case.h"
#include "../TypeCase.h"

// CaseFactory — Patron Factory pour la création centralisée des cases.
// Seule cette classe connaît les sous-classes concrètes (Mur, Passage, etc.).
// Le reste du code ne manipule que des Case* et des TypeCase.
class CaseFactory {
public:
    // Crée et retourne une case du type spécifié.
    // L'appelant prend la responsabilité de la mémoire (delete).
    static Case* creerCase(TypeCase type);
};

#endif // CASEFACTORY_H
