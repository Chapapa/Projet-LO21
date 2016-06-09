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
    Litterale (const QString t):type(t){}
    QString getType() const {return type;}
    void setType(QString s){type=s;}
    virtual QString toString()const=0;
    //virtual double getValue() const=0;
};



#endif // LITTERALE

