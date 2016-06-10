#ifndef ATOME
#define ATOME

#include "litterale.h"


/**
 *  \class Atome
 *  \brief Gestion des atomes
 *  \details La classe Atome herite de Litterale.
 *  Un atome est une suite de caracteres majuscules et de chiffres et commence par une lettre majuscule
 *  Un atome peut identifier un numerique, un programme ou une expression
 */
class Atome : public Litterale
{
    QString nom;
    Litterale* exp;
public:
    /**
     * \fn Atome(QString nom, Litterale* exp=nullptr)
     * \brief Constructeur de la classe Atome
     */
    Atome(QString nom, Litterale* exp=nullptr):nom(nom),exp(exp),Litterale("Atome"){}

    /**
     * \fn void setLitterale(Litterale& e)
     * \brief Accesseur en ecriture de l'attribut exp
     */
    void setLitterale(Litterale& e) { exp=&e; }

    /**
     * \fn QString getNom()
     * \brief Accesseur en lecture de l'attribut nom
     */
    QString getNom() const { return nom;}
    //Atome operatorFORGET(){ exp=nullptr; return *this; }
    Litterale& getLitterale() const;

    /**
     * \fn QString toString()const
     * \brief La methode convertie une expression en QString
     */
    QString toString()const
    {
        QString res=nom;
        return res;
    }

};


#endif // ATOME

