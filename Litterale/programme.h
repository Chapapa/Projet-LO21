#ifndef PROGRAMME
#define PROGRAMME

#include "litterale.h"
#include "computer.h"

// gestion espace tabulation retour chariot non faite
// pour EVAL ne pas mettre d'espace apres [ et avant ]


/**
 *  \class Programme
 *  \brief Gestion des programmes
 *  \details La classe programme herite de Litterale.
 *  Un programme est une suite d'operandes entree par l'utilisateur entre crochets
 */
class Programme : public Litterale
{
    QString prog;
public:

    /**
     * \fn  Programme(QString p)
     * \brief Constructeur de la classe Programme
     */
    Programme(QString p):prog(p),Litterale("Programme"){}

    /**
     * \fn QString getProg()
     * \brief Accesseur en lecture de l'attribut prog
     */
    QString getProg() const{return prog;}

    /**
     * \fn QString toString()const
     * \brief La methode convertie une expression en QString
     */
    QString toString()const {
        QString res= "["+prog+"]";
        return res;
    }
    QString toExpr()const;



};


#endif // PROGRAMME

