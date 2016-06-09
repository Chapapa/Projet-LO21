#include "litterale_mng.h"

#include "computer.h"
#include "programme.h"
#include "numerique.h"
#include "item.h"
#include "expression.h"

LitteraleManager::Handler LitteraleManager::handler=LitteraleManager::Handler();


/**
 * \fn void LitteraleManager::libererInstance()
 * \brief Design pattern singleton : liberation de l'instance
 */
void LitteraleManager::libererInstance()
{
    delete handler.instance;
    handler.instance=nullptr;
}


/**
 * \fn void LitteraleManager::agrandissementCapacite()
 * \brief Gestion des éventuels besoins en agrandissement du tableau de pointeurs de litterales
 */
void LitteraleManager::agrandissementCapacite()
{
    Litterale** newtab=new Litterale*[(nbMax+1)*2];
    for(unsigned int i=0; i<nb; i++) newtab[i]=exps[i];
    Litterale**  old=exps;
    exps=newtab;
    nbMax=(nbMax+1)*2;
    delete old;
}


/**
 * \fn Litterale& LitteraleManager::addLitteraleE(QString v)
 * \brief Alloue dynamiquement un objet Expression dont l’adresse est sauvegardée dans le tableau de pointeurs
 *  d’objets Litterale qui a été alloué dynamiquement
 */
Litterale& LitteraleManager::addLitteraleE(QString v)
{
    if (nb==nbMax) agrandissementCapacite();
    exps[nb++]=new Expression(v);
    return *exps[nb-1];
}

/**
 * \fn Litterale& LitteraleManager::addLitteraleA(QString v)
 * \brief Alloue dynamiquement un objet Atome dont l’adresse est sauvegardée dans le tableau de pointeurs
 *  d’objets Litterale qui a été alloué dynamiquement
 */
Litterale& LitteraleManager::addLitteraleA(QString v)
{
    if (nb==nbMax) agrandissementCapacite();
    exps[nb++]=new Atome(v);
    return *exps[nb-1];
}

/**
 * \fn Litterale& LitteraleManager::addLitteraleP(QString v)
 * \brief Alloue dynamiquement un objet Programme dont l’adresse est sauvegardée dans le tableau de pointeurs
 *  d’objets Litterale qui a été alloué dynamiquement
 */
Litterale& LitteraleManager::addLitteraleP(QString v)
{
    if (nb==nbMax) agrandissementCapacite();
    exps[nb++]=new Programme(v);
    return *exps[nb-1];
}
/**
 * \fn Litterale& LitteraleManager::addLitterale(int v)
 * \brief Alloue dynamiquement un objet Numerique de type "entier" dont l’adresse est sauvegardée dans le tableau de pointeurs
 *  d’objets Litterale qui a été alloué dynamiquement
 */
Litterale& LitteraleManager::addLitterale(int v)
{
    if (nb==nbMax) agrandissementCapacite();
    exps[nb++]=new Numerique(v);
    return *exps[nb-1];
}
/**
 * \fn Litterale& LitteraleManager::addLitterale(double v)
 * \brief Alloue dynamiquement un objet Numerique de type "reel" dont l’adresse est sauvegardée dans le tableau de pointeurs
 *  d’objets Litterale qui a été alloué dynamiquement
 */
Litterale& LitteraleManager::addLitterale(double v)
{
    if (nb==nbMax) agrandissementCapacite();
    exps[nb++]=new Numerique(v);
    return *exps[nb-1];
}

/**
 * \fn void LitteraleManager::removeLitterale(Litterale& e)
 * \brief Suppression d une litterale
 *
 * \param e Litterale a supprimer
 */
void LitteraleManager::removeLitterale(Litterale& e)
{
    unsigned int i=0;
    while(i<nb && exps[i]!=&e) i++;
    if (i==nb) throw ComputerException("elimination d'une Litterale inexistante");
    delete exps[i];
    i++;
    while(i<nb) { exps[i-1]=exps[i]; i++; }
    nb--;
}


/**
 * \fn LitteraleManager::~LitteraleManager()
 * \brief Destructeur de la classe LitteraleManager
 */
LitteraleManager::~LitteraleManager()
{
    for(unsigned int i=0; i<nb; i++) delete exps[i];
    delete[] exps;
}

/**
 * \fn Litterale& Item::getLitterale() const
 * \brief Accesseur en lecture pour l'attribut exp de la classe Item
 */
Litterale& Item::getLitterale() const
{
        if (exp==nullptr) throw ComputerException("Item : tentative d'acces a une Litterale inexistante");
        return *exp;
}
