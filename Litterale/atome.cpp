#include "atome.h"

/**
 * \fn Litterale& Atome::getLitterale() const
 * \brief Accesseur en lecture de l'attribut exp
 */
Litterale& Atome::getLitterale() const
{
        if (exp==nullptr) throw ComputerException("Atome : tentative d'acces a une Litterale inexistante");
        return *exp;
}

