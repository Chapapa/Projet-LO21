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
    Atome(QString nom, Litterale* exp=nullptr):nom(nom),exp(exp),Litterale("Atome"){}
    void setLitterale(Litterale& e) { exp=&e; }
    QString getNom() const { return nom;}
    //Atome operatorFORGET(){ exp=nullptr; return *this; }
    Litterale& getLitterale() const;
    QString toString()const
    {
        QString res=nom;
        return res;
    }

};


#endif // ATOME

