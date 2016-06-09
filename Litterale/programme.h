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
    Programme(QString p):prog(p),Litterale("Programme"){}
    QString getProg() const{return prog;}
    QString toString()const {
        QString res= "["+prog+"]";
        return res;
    }
    QString toExpr()const;



};


#endif // PROGRAMME

