#include "pile.h"



/**
 * \fn void Pile::agrandissementCapacite()
 * \brief Gestion des éventuels besoins en agrandissement du tableau d Items
 */
void Pile::agrandissementCapacite()
{
    Item* newtab=new Item[(nbMax+1)*2];
    for(unsigned int i=0; i<nb; i++) newtab[i]=items[i];
    Item*  old=items;
    items=newtab;
    nbMax=(nbMax+1)*2;
    delete[] old;
}

/**
 * \fn void Pile::push(Litterale& e)
 * \brief Empile une nouvelle litterale transmise par référence.
 */
void Pile::push(Litterale& e)
{
    if (nb==nbMax) agrandissementCapacite();
    items[nb].setLitterale(e);
    nb++;
    modificationEtat();
}

/**
 * \fn void Pile::pop()
 * \brief Depile l’objet Item au sommet de la pile
 */
void Pile::pop()
{
    nb--;
    items[nb].raz();
    modificationEtat();
}

/**
 * \fn void Pile::affiche(QTextStream& f) const
 * \brief Affiche la pile : message et litterales
 */
void Pile::affiche(QTextStream& f) const
{
    f<<"********************************************* \n";
    f<<"M : "<<message<<"\n";
    f<<"---------------------------------------------\n";
    for(unsigned int i=nbAffiche; i>0; i--) {
        if (i<=nb) f<<i<<": "<<items[nb-i].getLitterale().toString()<<"\n";
        else f<<i<<": \n";
    }
    f<<"---------------------------------------------\n";
}

/**
 * \fn Pile::~Pile()
 * \brief Destructeur de la classe pile
 */
Pile::~Pile()
{
    delete[] items;
}
/**
 * \fn void Pile::pop()
 * \brief Retourne une référence sur la litterale au sommet de la pile,
 */
Litterale& Pile::top() const
{
    if (nb==0) throw ComputerException("aucune Litterale sur la pile");
    return items[nb-1].getLitterale();
}
