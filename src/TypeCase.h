#ifndef TYPECASE_H
#define TYPECASE_H

// Enumération des types de cases du donjon.
// Utilisée par CaseFactory pour instancier la bonne sous-classe.
enum class TypeCase {
    MUR,
    PASSAGE,
    TRESOR,
    MONSTRE,
    PIEGE
};

#endif // TYPECASE_H
