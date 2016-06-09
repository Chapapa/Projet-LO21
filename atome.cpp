#include "atome.h"


Litterale& Atome::getLitterale() const
{
        if (exp==nullptr) throw ComputerException("Atome : tentative d'acces a une Litterale inexistante");
        return *exp;
}

/**
 * \fn Atome Expression::operatorSTO(Litterale& l)
 * \brief Operateur pour asssocier une litterale et un identificateur
 *
 * \param l Litterale a stocker
 *
 * \return La methode retourne l'atome pointant sur la literale stockee
 */
