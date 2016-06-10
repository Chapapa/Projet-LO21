#include "expression.h"

#include "computer.h"

#include "numerique.h"
#include "programme.h"

/**
 * \fn bool estUnIdentificateur(const Expression& e)
 * \brief Test si l'expression passee en argument est un identificateur
 */
bool estUnIdentificateur(const Expression& e)
{
    int i=0;
    QString s=e.getExp();
    if (s[i] >= 'A' && s[i] <= 'Z')
    {
         while (i<(e.getExp().length()))
         {
             if((s[i] < 'A' && s[i] > 'Z') || (s[i] < '0' && s[i] > '9'))
                 return false;
             i++;
         }
         return true;
    }
    return false;

}

/**
 * \fn Atome Expression::operatorSTO(Litterale& l)
 * \brief Operateur pour asssocier une litterale et un identificateur
 *
 * \param l Litterale a stocker
 *
 * \return La methode retourne l'atome pointant sur la literale stockee
 */

Atome Expression::operatorSTO(Litterale& l)
{
    if (l.getType()=="Numerique")
    {
        Numerique n=dynamic_cast<Numerique&>(l);
        return Atome(exp,new Numerique(n));
    }
    if (l.getType()=="Expression")
    {
        Expression n=dynamic_cast<Expression&>(l);
        return Atome(exp,new Expression(n));
    }
    if (l.getType()=="Programme")
    {
        Programme n=dynamic_cast<Programme&>(l);
        return Atome(exp,new Programme(n));
    }
    return NULL;
}

/**
 * \fn Expression Expression::operator<=(const Expression& e)
 * \brief Operateur <=
 */
Expression Expression::operator<=(const Expression& e)
{
    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' )
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '+' || e.exp[i] == '-' || e.exp[i] == '*' || e.exp[i] == '/')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+"<="+e.exp;
    else
        res= "("+exp+")<=("+e.exp+")";
    return Expression(res);
}

/**
 * \fn Expression Expression::operator>=(const Expression& e)
 * \brief Operateur >=
 */
Expression Expression::operator>=(const Expression& e)
{
    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' )
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '+' || e.exp[i] == '-' || e.exp[i] == '*' || e.exp[i] == '/')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+">="+e.exp;
    else
        res= "("+exp+")>=("+e.exp+")";
    return Expression(res);
}

/**
 * \fn Expression Expression::operator<(const Expression& e)
 * \brief Operateur <
 */
Expression Expression::operator<(const Expression& e)
{
    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' )
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '+' || e.exp[i] == '-' || e.exp[i] == '*' || e.exp[i] == '/')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+"<"+e.exp;
    else
        res= "("+exp+")<("+e.exp+")";
    return Expression(res);
}

/**
 * \fn Expression Expression::operator>(const Expression& e)
 * \brief Operateur >
 */
Expression Expression::operator>(const Expression& e)
{
    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' )
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '+' || e.exp[i] == '-' || e.exp[i] == '*' || e.exp[i] == '/')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+">"+e.exp;
    else
        res= "("+exp+")>("+e.exp+")";
    return Expression(res);
}

/**
 * \fn Expression Expression::operator!=(const Expression& e)
 * \brief Operateur !=
 */
Expression Expression::operator!=(const Expression& e)
{

    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '<' || exp[i] == '>' || exp[i] == '<=' || exp[i] == '>=')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '+' || e.exp[i] == '-' || e.exp[i] == '*' || e.exp[i] == '/' || e.exp[i] == '<' || e.exp[i] == '>' || e.exp[i] == '<=' || e.exp[i] == '>=')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+"!="+e.exp;
    else
        res= "("+exp+")!=("+e.exp+")";
    return Expression(res);
}

/**
 * \fn Expression Expression::operator==(const Expression& e)
 * \brief Operateur ==
 */
Expression Expression::operator==(const Expression& e)
{

    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '<' || exp[i] == '>' || exp[i] == '<=' || exp[i] == '>=')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '+' || e.exp[i] == '-' || e.exp[i] == '*' || e.exp[i] == '/' || e.exp[i] == '<' || e.exp[i] == '>' || e.exp[i] == '<=' || e.exp[i] == '>=')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+"=="+e.exp;
    else
        res= "("+exp+")==("+e.exp+")";
    return Expression(res);
}

/**
 * \fn Expression Expression::operatorAND(const Expression& e)
 * \brief Operateur AND
 */
Expression Expression::operatorAND(const Expression& e)
{
    QString res;
    res="AND("+exp+","+e.exp+")";

    return Expression(res);
}

/**
 * \fn Expression Expression::operatorOR(const Expression& e)
 * \brief Operateur OR
 */
Expression Expression::operatorOR(const Expression& e)
{
    QString res;
    res="OR("+exp+","+e.exp+")";

    return Expression(res);
}

/**
 * \fn Expression Expression::operatorNOT()
 * \brief Operateur NOT
 */
Expression Expression::operatorNOT()
{
    QString res;
    res="NOT("+exp+")";

    return Expression(res);
}

/**
 * \fn Expression Expression::operatorNEG()
 * \brief Operateur NEG
 */
Expression Expression::operatorNEG()
{
    QString res;
    res="NEG("+exp+")";

    return Expression(res);
}

/**
 * \fn Expression Expression::operator*(const Expression& e)
 * \brief Operateur *
 */
Expression Expression::operator*(const Expression& e)
{
    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '+' || exp[i] == '-')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '-' || e.exp[i] == '+')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+"*"+e.exp;
    else
        res= "("+exp+")*("+e.exp+")";
    return Expression(res);
}

/**
 * \fn Expression Expression::operator/(const Expression& e)
 * \brief Operateur /
 */
Expression Expression::operator/(const Expression& e)
{
    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '+' || exp[i] == '-')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '-' || e.exp[i] == '+')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+"/"+e.exp;
    else
        res= "("+exp+")/("+e.exp+")";
    return Expression(res);

}

/**
 * \fn Expression Expression::operator$(const Expression& e)
 * \brief Operateur $
 */
Expression Expression::operator$(const Expression& e)
{
    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '+' || e.exp[i] == '-' || e.exp[i] == '*' || e.exp[i] == '/')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+"$"+e.exp;
    else
        res= "("+exp+")$("+e.exp+")";
    return Expression(res);
}

/**
 * \fn Expression Expression::operator+(const Expression& e)
 * \brief Operateur +
 */
Expression Expression::operator+(const Expression& e)
{
    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '/' || exp[i] == '*' ||  exp[i] == '$')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '/' || e.exp[i] == '*' ||  exp[i] == '$')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+"+"+e.exp;
    else
        res= "("+exp+")+("+e.exp+")";
    return Expression(res);
}

/**
 * \fn Expression Expression::operator-(const Expression& e)
 * \brief Operateur -
 */
Expression Expression::operator-(const Expression& e)
{
    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '/' || exp[i] == '*' ||  exp[i] == '$')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '/' || e.exp[i] == '*' ||  exp[i] == '$')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+"-"+e.exp;
    else
        res= "("+exp+")-("+e.exp+")";
    return Expression(res);
}
