#ifndef CASEFACTORY_H
#define CASEFACTORY_H
#include "Case.h"
#include "../TypeCase.h"
class CaseFactory {
public:
    static Case* creerCase(TypeCase type);
};
#endif 