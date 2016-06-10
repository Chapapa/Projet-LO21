#ifndef EXPRESSION
#define EXPRESSION

#include "litterale.h"
#include "atome.h"

/**
 *  \class Expression
 *  \brief Gestion des expressions
 *
 * \details La classe Expression herite de la classe Litterale. Elle gère la manipulation des nombres réels,rationnels, complexes et entiers.
 */
class Expression : public Litterale
{
    QString exp;
public :
    /**
     * \fn Expression(QString e)
     * \brief Constructeur de la classe Expression
     */
    Expression(QString e):exp(e),Litterale("Expression"){}

    /**
     * \fn QString getExp()
     * \brief Accesseur en lecture de l'attribut exp
     */
    QString getExp() const{return exp;}

    /**
     * \fn QString toString()const
     * \brief La methode convertie une expression en QString
     */
    QString toString()const {
        QString res= "'"+exp+"'";
        return res;
    }

    Expression operator+(const Expression& n);
    Expression operator-(const Expression& n);
    Expression operator*(const Expression& n);
    Expression operator/(const Expression& n);
    Expression operatorAND(const Expression& n);
    Expression operatorOR(const Expression& n);
    Expression operatorNOT();
    Expression operatorNEG();

    Expression operator$(const Expression& e);
    Expression operator==(const Expression& n);
    Expression operator!=(const Expression& n);
    Expression operator<=(const Expression& n);
    Expression operator>=(const Expression& n);
    Expression operator<(const Expression& n);
    Expression operator>(const Expression& n);
    //Expression operatorEVAL();
    Atome operatorSTO(Litterale& l);

};

bool estUnIdentificateur(const Expression& e);

#endif // EXPRESSION

