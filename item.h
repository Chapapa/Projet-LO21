#ifndef ITEM
#define ITEM

#include "computer.h"

/**
 *  \class Item
 *  \brief Gestion des items
 *
 * \details La classe Item encapsule un attribut exp de type Litterale* qui contient l’adresse d’un objet Litterale à afficher.
 */

class Item
{
    Litterale* exp;
public:
    /**
     * \fn Item():exp(nullptr)
     * \brief Constructeur
     */
    Item():exp(nullptr){}

    /**
     * \fn void setLitterale(Litterale& e)
     * \brief Accesseur en ecriture de l'attribut exp
     */
    void setLitterale(Litterale& e) { exp=&e; }

    /**
     * \fn void raz()
     * \brief Remise a zero de l'item
     */
    void raz() { exp=0; }
    Litterale& getLitterale() const;
};


#endif // ITEM

