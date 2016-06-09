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
    Item():exp(nullptr){}
    void setLitterale(Litterale& e) { exp=&e; }
    void raz() { exp=0; }
    Litterale& getLitterale() const;
};


#endif // ITEM

