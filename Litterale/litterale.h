#ifndef LITTERALE
#define LITTERALE
#include "computer.h"

/**
 *  \class Litterale
 *  \brief Gestion des litterales
 *  \details Il s'agit d'une classe abstraite, dont tous les types de litterale vont heriter.
 *   Grace au polymorphisme, cette classe nous permet de stocker a la fois les litterales numeriques, atomes, expressions et programmes dans un meme tableau.
 */
class Litterale
{
    QString type;
    friend class LitteraleManager;
public:
    /**
     * \fn Litterale (const QString t)
     * \brief Constructeur de la classe Litterale
     */
    Litterale (const QString t):type(t){}

    /**
     * \fn QString getType() const
     * \brief Accesseur en lecture de l'attribut type
     */
    QString getType() const {return type;}

    /**
     * \fn QString setType() const
     * \brief Accesseur en ecriture de l'attribut type
     */
    void setType(QString s){type=s;}

    /**
     * \fn QString toString()const
     * \brief La methode convertie une expression en QString
     */
    virtual QString toString()const=0;
    //virtual double getValue() const=0;
};



#endif // LITTERALE

