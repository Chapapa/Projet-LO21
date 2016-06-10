#include "controleur.h"
#include "Litterale/litterale.h"
#include "computer.h"


/**
 * \fn int Controleur::chercherAtome(QString s)
 * \brief Cherche si un atome est deja utilise comme identificateur
 * \return La methode retourne la position de l'atome si il existe, -1 sinon.

 */
int Controleur::chercherAtome(QString s)
{
    for(int i=nbAtomes-1; i>=0; i--)
    {
        if ((*atomes[i]).getType()=="Atome")
        {
            Atome a=dynamic_cast<Atome&>(*atomes[i]);
            if (a.getNom()==s)
                return i;
        }
    }
    return -1;
}

/**
 * \fn void Controleur::agrandissementCapacite()
 * \brief Gestion des éventuels besoins en agrandissement du tableau d Atome
 */
void Controleur::agrandissementCapacite()
{
    Atome** newtab=new Atome*[(nbAtomesMax+1)*2];
    for(unsigned int i=0; i<nbAtomes; i++) newtab[i]=atomes[i];
    Atome**  old=atomes;
    atomes=newtab;
    nbAtomesMax=(nbAtomesMax+1)*2;
    delete[] old;
}

/**
 * \fn void Controleur::removeAtome(Atome& e)
 * \brief Suppression d un atome
 *
 * \param e Atome a supprimer
 */
void Controleur::removeAtome(Atome& e)
{
    unsigned int i=0;
    while(i<nbAtomes && atomes[i]!=&e) i++;
    if (i==nbAtomes) throw ComputerException("elimination d'une Litterale inexistante");
    delete atomes[i];
    i++;
    while(i<nbAtomes) { atomes[i-1]=atomes[i]; i++; }
    nbAtomes--;
}

/**
 * \fn Numerique Controleur::manageNumOpeNumAndNum(Numerique v1, Numerique v2, QString s, Numerique res, bool beep)
 * \brief Gestion des operations numeriques binaires entre 2 Numeriques
 * \param v1 2e Numerique depile
 * \param v2 1er Numerique depile
 * \param s operateur a appliquer
 * \param res Variable ou stocker le resultat
 * \param beep bip sonore
 */
Numerique Controleur::manageNumOpeNumAndNum(Numerique v1, Numerique v2, QString s, Numerique res, bool beep)
{
    if (s == "+") res = v1 + v2;
    if (s == "-") res = v1 - v2;
    if (s == "*") res = v1 * v2;
    if (s == "$")
    {
        if(v2.getTypeIm() != "null" || v1.getTypeIm() != "null")
        {
            if(beep)
                Beep(500,500);
            expAff.setMessage("Erreur : au moins une litterale est deja complexe");
            Litterale& l=expMng.addLitterale(v1);
            expAff.push(l);
            res=v2;
        }
        else
        {
            res = v1.operator$(v2);
        }
    }
    if (s == "/")
    {
        //if (v2 != 0)
        if(v2.getNumReel() != 0 || v2.getNumIm() != 0)
            res = v1 / v2;
        else
        {
            if(beep)
                Beep(500,500);
            expAff.setMessage("Erreur : division par zéro");
            res = v1;
        }
    }
    if (s == "DIV")
    {
        if(v2.getTypeIm() == "null" && v1.getTypeIm() == "null" && v2.getTypeRe() == "entier" && v1.getTypeRe() == "entier")
        {
            res = v1.operatorDIV(v2);
        }

        else
        {
            if(beep)
                Beep(500,500);
            expAff.setMessage("Erreur : au moins une litterale n'est pas entiere");
            Litterale& l=expMng.addLitterale(v1);
            expAff.push(l);
            res=v2;
        }
    }
    if (s == "MOD")
    {
        if(v2.getTypeIm() == "null" && v1.getTypeIm() == "null" && v2.getTypeRe() == "entier" && v1.getTypeRe() == "entier")
        {
            res = v1.operatorMOD(v2);
        }

        else
        {
            if(beep)
                Beep(500,500);
            expAff.setMessage("Erreur : au moins une litterale n'est pas entiere");
            Litterale& l=expMng.addLitterale(v1);
            expAff.push(l);
            res=v2;
        }
    }
    return res;
}
/**
 * \fn Numerique Controleur::manageLogicOpeNumAndNum(Numerique v1, Numerique v2, QString s, Numerique res, bool beep)
 * \brief Gestion des operations logiques binaires entre 2 Numeriques
 * \param v1 2e Numerique depile
 * \param v2 1er Numerique depile
 * \param s operateur a appliquer
 * \param res Variable ou stocker le resultat
 * \param beep bip sonore
 */
Numerique Controleur::manageLogicOpeNumAndNum(Numerique v1, Numerique v2, QString s, Numerique res, bool beep)
{
    if (s == "==")
    {
        res=v1==v2;
    }
    if (s == "!=")
    {
        res=v1!=v2;
    }
    if (s == ">=")
    {
       if(v2.getTypeIm() == "null" && v1.getTypeIm() == "null")
            res=v1>=v2;
       else
       {
           if(beep)
               Beep(500,500);
           expAff.setMessage("Erreur : on ne peut pas comparer les complexes");
           Litterale& l=expMng.addLitterale(v1);
           expAff.push(l);
           res=v2;
       }
    }

    if (s == "<=")
    {
       if(v2.getTypeIm() == "null" && v1.getTypeIm() == "null")
            res=v1<=v2;
       else
       {
           if(beep)
               Beep(500,500);
           expAff.setMessage("Erreur : on ne peut pas comparer les complexes");
           Litterale& l=expMng.addLitterale(v1);
           expAff.push(l);
           res=v2;
       }
    }

    if (s == ">")
    {
       if(v2.getTypeIm() == "null" && v1.getTypeIm() == "null")
            res=v1>v2;
       else
       {
           if(beep)
               Beep(500,500);
           expAff.setMessage("Erreur : on ne peut pas comparer les complexes");
           Litterale& l=expMng.addLitterale(v1);
           expAff.push(l);
           res=v2;
       }
    }

    if (s == "<")
    {
       if(v2.getTypeIm() == "null" && v1.getTypeIm() == "null")
            res=v1<v2;
       else
       {
           if(beep)
               Beep(500,500);
           expAff.setMessage("Erreur : on ne peut pas comparer les complexes");
           Litterale& l=expMng.addLitterale(v1);
           expAff.push(l);
           res=v2;
       }
    }

    if (s == "AND")
    {
        res=v1.operatorAND(v2);
    }
    if (s == "OR")
    {
        res=v1.operatorOR(v2);
    }
    return res;
}

/*Numerique Controleur::managePileOpeNumAndNum(Numerique v1, Numerique v2,QString s, Numerique res)
{
    if (s == "SWAP")
    {
        res=v1;
        Litterale& l=expMng.addLitterale(v2);
        expAff.push(l);
    }
    return res;
}*/
/**
 * \fn Expression Controleur::manageNumOpeNumAndExpr(Expression v1, Expression v2E, QString s, Expression res)
 * \brief Gestion des operations numeriques binaires entre une Expression et un Numerique
 * \param v1 2e Litterale depilee (Expression)
 * \param v2 1er Litterale depilee (Numerique converti en Expression)
 * \param s operateur a appliquer
 * \param res Variable ou stocker le resultat
 */
Expression Controleur::manageNumOpeNumAndExpr(Expression v1, Expression v2E, QString s, Expression res)
{
    if (s == "+") res = v1 + v2E;
    if (s == "-") res = v1 - v2E;
    if (s == "*") res = v1 * v2E;
    if (s == "/") res = v1 / v2E;
    if (s == "$") res = v1.operator$(v2E);
    return res;
}
/**
 * \fn Expression Controleur::manageLogicOpeNumAndExpr(Expression v1, Expression v2E, QString s, Expression res)
 * \brief Gestion des operations logiques binaires entre une Expression et un Numerique
 * \param v1 2e Litterale depilee (Expression)
 * \param v2 1er Litterale depilee (Numerique converti en Expression)
 * \param s operateur a appliquer
 * \param res Variable ou stocker le resultat
 */
Expression Controleur::manageLogicOpeNumAndExpr(Expression v1, Expression v2E, QString s, Expression res)
{
    if (s == "AND") res = v1.operatorAND(v2E);
    if (s == "OR") res = v1.operatorOR(v2E);
    if (s == "==") res = v1.operator==(v2E);
    if (s == "!=") res = v1.operator!=(v2E);
    if (s == "<=") res = v1.operator<=(v2E);
    if (s == ">=") res = v1.operator>=(v2E);
    if (s == "<") res = v1.operator<(v2E);
    if (s == ">") res = v1.operator>(v2E);
    return res;
}

/*Expression Controleur::managePileOpeNumAndExpr(Expression v1, Numerique v2,QString s, Expression res)
{
    if (s == "SWAP")
    {
        res=v1;
        Litterale& l=expMng.addLitterale(v2);
        expAff.push(l);
    }
    return res;
}*/
/**
 * \fn Expression Controleur::manageNumOpeExprAndExpr(Expression v1, Expression v2, QString s, Expression res)
 * \brief Gestion des operations numeriques binaires entre 2 expressions
 * \param v1 2e Expression depilee
 * \param v2 1er Expression depilee
 * \param s operateur a appliquer
 * \param res Variable ou stocker le resultat
 * \param beep bip sonore
 */
Expression Controleur::manageNumOpeExprAndExpr(Expression v1, Expression v2, QString s, Expression res)
{
    if (s == "+") res = v1 + v2;
    if (s == "-") res = v1 - v2;
    if (s == "*") res = v1 * v2;
    if (s == "/") res = v1 / v2;
    if (s == "$") res = v1.operator$(v2);
    return res;
}
/**
 * \fn Expression Controleur::manageLogicOpeExprAndExpr(Expression v1, Expression v2, QString s, Expression res)
 * \brief Gestion des operations logiques binaires entre 2 expressions
 * \param v1 2e Expression depile
 * \param v2 1er Expression depile
 * \param s operateur a appliquer
 * \param res Variable ou stocker le resultat
 * \param beep bip sonore
 */
Expression Controleur::manageLogicOpeExprAndExpr(Expression v1, Expression v2, QString s, Expression res)
{
    if (s == "AND") res = v1.operatorAND(v2);
    if (s == "OR") res = v1.operatorOR(v2);
    if (s == "==") res = v1.operator==(v2);
    if (s == "!=") res = v1.operator!=(v2);
    if (s == "<=") res = v1.operator<=(v2);
    if (s == ">=") res = v1.operator>=(v2);
    if (s == "<") res = v1.operator<(v2);
    if (s == ">") res = v1.operator>(v2);

    return res;
}

/*Expression Controleur::managePileOpeExprAndExpr(Expression v1, Expression v2,QString s, Expression res)
{
    if (s == "SWAP")
    {
        res=v1;
        Litterale& l=expMng.addLitterale(v2);

        expAff.push(l);

    }
    return res;
}
*/
Expression Controleur::manageNumOpeExprAndNum(Expression v1E, Expression v2, QString s, Expression resE)
{
    if (s == "+") resE = v1E + v2;
    if (s == "-") resE = v1E - v2;
    if (s == "*") resE = v1E * v2;
    if (s == "/") resE = v1E / v2;
    if (s == "$") resE = v1E.operator$(v2);
    return resE;
}

Expression Controleur::manageLogicOpeExprAndNum(Expression v1E, Expression v2, QString s, Expression resE)
{
    if (s == "AND") resE = v1E.operatorAND(v2);
    if (s == "OR") resE = v1E.operatorOR(v2);
    if (s == "==") resE = v1E.operator==(v2);
    if (s == "!=") resE = v1E.operator!=(v2);
    if (s == "<=") resE = v1E.operator<=(v2);
    if (s == ">=") resE = v1E.operator>=(v2);
    if (s == "<") resE = v1E.operator<(v2);
    if (s == ">") resE = v1E.operator>(v2);
    return resE;
}

/*Numerique Controleur::managePileOpeExprAndNum(Numerique v1, Expression v2,QString s, Numerique res)
{
    if (s == "SWAP")
    {
        res=v1;
        Litterale& l=expMng.addLitterale(v2);
        expAff.push(l);

        Litterale& e=expMng.addLitterale(res);
        expAff.push(e);
    }
    return res;
}*/

Atome Controleur::manageAtomeOpeNumAndExpr(Numerique v1, Expression v2,QString s, Atome res)
{
    if (s == "STO")
    {
        res=v2.operatorSTO(v1);
    }
    addAtome(res);
    expAff.atomeAdded();
    return res;
}

Atome Controleur::manageAtomeOpeExprAndExpr(Expression v1, Expression v2,QString s, Atome res)
{
    if (s == "STO")
    {
        res=v2.operatorSTO(v1);
    }
    addAtome(res);
    expAff.atomeAdded();
    return res;
}

Atome Controleur::manageAtomeOpePrgmAndExpr (Programme v1, Expression v2,QString s, Atome res)
{
    if (s == "STO")
    {
        res=v2.operatorSTO(v1);
    }
    addAtome(res);
    expAff.atomeAdded();
    return res;
}


void Controleur::getRationnel(QString s, int &i, int &j, const QString& c)
{
    Numerique v1(s.toInt());
    i++;
    j = i;
    while(i < (c.length()-1) && !estUnOperateurBinaire(c[i]) && c[i]!=' ')
    {
        i++;
    }
    if(i == c.length()-1)
    {
        i++;
    }
    s = c.mid(j,i-j);
    Numerique v2 = s.toInt();
    Numerique res(v1.getNumReel(), v2.getNumReel());
    Litterale& e=expMng.addLitterale(res);
    expAff.push(e);
}

void Controleur::manageBinOpe(bool beep, QString s)
{
    try
    {

        if(expAff.top().getType()=="Numerique") // La premier littérale saisie est numérique
        {
            Numerique v2=dynamic_cast<Numerique&>(expAff.top());
            expMng.removeLitterale(expAff.top());
            expAff.pop();

            if(expAff.top().getType()=="Numerique") // La deuxième littérale saisie est numérique
            {
                Numerique v1=dynamic_cast<Numerique&>(expAff.top());
                expMng.removeLitterale(expAff.top());
                expAff.pop();

                Numerique res(0);// on initialise res a zero


                res = manageNumOpeNumAndNum(v1, v2, s, res, beep);

                res = managePileOpeT2AndT1(v1, v2, s, res);

                res = manageLogicOpeNumAndNum(v1, v2, s, res, beep);

                Litterale& e=expMng.addLitterale(res);

                expAff.push(e);
            } // if v1 Numerique
            else if(expAff.top().getType()=="Expression") // La deuxième littérale saisie est une expression
            {
                Expression v1=dynamic_cast<Expression&>(expAff.top());
                expMng.removeLitterale(expAff.top());
                expAff.pop();

                Expression res("");

                res = managePileOpeT2AndT1(v1, v2,s, res);

                Expression v2E=v2.toString();

                res = manageNumOpeNumAndExpr(v1, v2E, s, res);

                res = manageLogicOpeNumAndExpr(v1, v2E, s, res);

                Litterale& e=expMng.addLitterale(res);
                expAff.push(e);
            }// else v1 expression
            else if(expAff.top().getType()=="Programme")
            {
                Programme v1=dynamic_cast<Programme&>(expAff.top());
                expMng.removeLitterale(expAff.top());
                expAff.pop();


                if (s=="SWAP")
                {
                    Programme res("");
                    res=managePileOpeT2AndT1(v1, v2,s, res);
                    Litterale& e=expMng.addLitterale(res);

                    expAff.push(e);
                }
            }

        }//if v2 Numerique
        else if(expAff.top().getType()=="Expression") // La première littérale saisie est une expression
        {
            Expression v2=dynamic_cast<Expression&>(expAff.top());
            expMng.removeLitterale(expAff.top());
            expAff.pop();

            if(expAff.top().getType()=="Expression") // La deuxième littérale saisie est une expression
            {
                Expression v1=dynamic_cast<Expression&>(expAff.top());
                expMng.removeLitterale(expAff.top());
                expAff.pop();

                if (s=="STO")
                {
                    Atome resA("");
                    if(!estUnOperateurBinaire(v2.getExp())&& !estUnOperateurUnaire(v2.getExp())&& !estUnOperateurSansArg(v2.getExp())
                            && estUnIdentificateur(v2))
                    {
                        resA = manageAtomeOpeExprAndExpr(v1, v2,s, resA);
                        //Litterale& e=expMng.addLitterale(resA);
                        Litterale& e=expMng.addLitterale(v1);
                        expAff.push(e);
                    }
                    else
                    {
                        expAff.setMessage("L'identificateur ne peut pas correspondre a un operateur et doit etre un atome");
                        Litterale& e=expMng.addLitterale(v1);

                        expAff.push(e);
                    }
                    //i++;
                    //j = i;
                    return;
                }

                Expression res("");// on initialise res a zero

                res = manageNumOpeExprAndExpr(v1, v2, s, res);

                res = manageLogicOpeExprAndExpr(v1, v2, s, res);

                res = managePileOpeT2AndT1(v1, v2, s, res);

                Litterale& e=expMng.addLitterale(res);

                expAff.push(e);
            }//if v1 expression

            else if(expAff.top().getType()=="Numerique") // La deuxième littérale saisie est numérique
            {
                Numerique v1=dynamic_cast<Numerique&>(expAff.top());
                expMng.removeLitterale(expAff.top());
                expAff.pop();

                Numerique res(0);

                if (s=="STO")
                {
                    Atome resA("");
                    if(!estUnOperateurBinaire(v2.getExp()) && !estUnOperateurUnaire(v2.getExp()) &&
                            !estUnOperateurSansArg(v2.getExp()) && estUnIdentificateur(v2))
                    {
                        resA = manageAtomeOpeNumAndExpr(v1, v2,s, resA);
                        //Litterale& e=expMng.addLitterale(resA);
                        Litterale& e=expMng.addLitterale(v1);

                        expAff.push(e);
                    }
                    else
                    {
                        expAff.setMessage("L'identificateur ne peut pas correspondre a un operateur et doit etre un atome ");
                        Litterale& e=expMng.addLitterale(v1);

                        expAff.push(e);
                    }
                    //i++;
                    //j = i;
                    //expAff.setMessage(resA.getLitterale().toString());
                    return;
                }

                if (s == "SWAP")
                {
                    res = managePileOpeT2AndT1(v1, v2, s, res);
                    Litterale& e=expMng.addLitterale(res);

                    expAff.push(e);
                }
                else
                {
                    Expression v1E=v1.toString();
                    Expression resE("");
                    resE = manageNumOpeExprAndNum(v1E, v2, s, resE);
                    resE = manageLogicOpeExprAndNum(v1E, v2, s, resE);

                    Litterale& e=expMng.addLitterale(resE);
                    expAff.push(e);
                }


            }//if v1 Numerique

            else if(expAff.top().getType()=="Programme")
            {
                Programme v1=dynamic_cast<Programme&>(expAff.top());
                expMng.removeLitterale(expAff.top());
                expAff.pop();

                if (s=="STO")
                {
                    Atome resA("");
                    if(!estUnOperateurBinaire(v2.getExp()) && !estUnOperateurUnaire(v2.getExp()) && !estUnOperateurSansArg(v2.getExp()) && estUnIdentificateur(v2))
                    {
                        resA = manageAtomeOpePrgmAndExpr(v1, v2,s, resA);
                        //Litterale& e=expMng.addLitterale(resA.getLitterale());
                        Litterale& e=expMng.addLitterale(v1);

                        expAff.push(e);
                    }
                    else
                    {
                        expAff.setMessage("L'identificateur ne peut pas correspondre a un operateur et doit etre un atome ");
                        Litterale& e=expMng.addLitterale(v1);

                        expAff.push(e);
                    }
                    //i++;
                    //j = i;
                    //expAff.setMessage(resA.getLitterale().toString());
                    return;
                }
                else if (s=="SWAP")
                {
                    Programme res("");
                    res=managePileOpeT2AndT1(v1, v2,s, res);
                    Litterale& e=expMng.addLitterale(res);

                    expAff.push(e);
                }
                else
                {

                        // transformation programme en expression
                        QString str=v1.toExpr();
                        expAff.setMessage(str);
                        commande(str, true);

                        Expression v3=dynamic_cast<Expression&>(expAff.top());
                        expMng.removeLitterale(expAff.top());
                        expAff.pop();

                        Expression res("");// on initialise res a zero

                        res = manageNumOpeExprAndExpr(v3, v2, s, res);

                        res = manageLogicOpeExprAndExpr(v3, v2, s, res);

                        //res = managePileOpeExprAndExpr(v3, v2, s, res);

                        Litterale& e=expMng.addLitterale(res);

                        expAff.push(e);

                }
            }

        }// else v2 expression
        else if(expAff.top().getType()=="Programme")
        {
            Programme v2=dynamic_cast<Programme&>(expAff.top());
            expMng.removeLitterale(expAff.top());
            expAff.pop();

            if(expAff.top().getType()=="Expression") // La deuxième littérale saisie est une expression
            {

                Expression v1=dynamic_cast<Expression&>(expAff.top());
                expMng.removeLitterale(expAff.top());
                expAff.pop();

                    if (s=="SWAP")
                    {
                        Expression res("");
                        res=managePileOpeT2AndT1(v1, v2,s, res);
                        Litterale& e=expMng.addLitterale(res);

                        expAff.push(e);
                    }
                    else// transformation programme en expression
                    {
                        // transformation programme en expression
                        QString str=v2.toExpr();
                        expAff.setMessage(str);
                        commande(str, true);

                        Expression v3=dynamic_cast<Expression&>(expAff.top());
                        expMng.removeLitterale(expAff.top());
                        expAff.pop();

                        Expression res("");// on initialise res a zero

                        res = manageNumOpeExprAndExpr(v1, v3, s, res);

                        res = manageLogicOpeExprAndExpr(v1, v3, s, res);

                        //res = managePileOpeExprAndExpr(v1, v3, s, res);

                        Litterale& e=expMng.addLitterale(res);

                        expAff.push(e);
                    }
                }

                else if(expAff.top().getType()=="Numerique")
                {
                    Numerique v1=dynamic_cast<Numerique&>(expAff.top());
                    expMng.removeLitterale(expAff.top());
                    expAff.pop();
                    if (s=="SWAP")
                    {
                        Numerique res(0);
                        res=managePileOpeT2AndT1(v1, v2,s, res);
                        Litterale& e=expMng.addLitterale(res);

                        expAff.push(e);
                    }
                }
                else if(expAff.top().getType()=="Programme")
                {
                    Programme v1=dynamic_cast<Programme&>(expAff.top());
                    expMng.removeLitterale(expAff.top());
                    expAff.pop();
                    if (s=="SWAP")
                    {
                        Programme res("");
                        res=managePileOpeT2AndT1(v1, v2,s, res);
                        Litterale& e=expMng.addLitterale(res);

                        expAff.push(e);
                    }
                }
            }


    } //try
    catch(std::bad_cast& e)
    {
        if(beep)
            Beep(500,500);
        expAff.setMessage(e.what());
    }


}

void Controleur::manageUnOpe(bool beep, QString s)
{

    if(expAff.top().getType()=="Numerique")
    {
        try
        {
            //double v1=expAff.top().getValue();
            Numerique v1=dynamic_cast<Numerique&>(expAff.top());
            expMng.removeLitterale(expAff.top());
            expAff.pop();
            //double res;
            Numerique res(0);// on initialise res a zero


            if (s == "NEG") res = v1.operatorNEG();
            if (s == "NUM")
            {
                if(v1.getTypeIm() == "null" || (v1.getTypeRe() == "entier" || v1.getTypeRe() == "rationnel" ))
                {
                    res = v1.operatorNUM();
                }

                else
                {
                    if(beep)
                        Beep(500,500);
                    expAff.setMessage("Erreur : la litterale n'est ni entiere ni rationnelle");
                    res = v1;
                }
            }
            if (s == "DEN")
            {
                if(v1.getTypeIm() == "null" || (v1.getTypeRe() == "entier" || v1.getTypeRe() == "rationnel" ))
                {
                    res = v1.operatorDEN();
                }

                else
                {
                    if(beep)
                        Beep(500,500);
                    expAff.setMessage("Erreur : la litterale n'est ni entiere ni rationnelle");
                    res = v1;
                }
            }
            if (s == "RE")
            {
                if(v1.getTypeIm() != "null")
                {
                    res = v1.operatorRE();
                }

                else
                {
                    if(beep)
                        Beep(500,500);
                    expAff.setMessage("Erreur : la litterale n'est pas complexe");
                    res = v1;
                }
            }
            if (s == "IM")
            {
                if(v1.getTypeIm() != "null")
                {
                    res = v1.operatorIM();
                }

                else
                {
                    if(beep)
                        Beep(500,500);
                    expAff.setMessage("Erreur : la litterale n'est pas complexe");
                    res = v1;
                }
            }
            if (s== "DUP")
            {
                res= v1;
                Litterale& l=expMng.addLitterale(res);
                expAff.push(l);
            }
            if (s== "DROP")
            {
                //i++;
                //j = i;
                return;
            }
            if (s == "NOT")
            {
                res=v1.operatorNOT();
            }
            Litterale& e=expMng.addLitterale(res);

            expAff.push(e);
        }
        catch(std::bad_cast& e)
        {
            if(beep)
                Beep(500,500);
            expAff.setMessage(e.what());
        }
    }
    else if(expAff.top().getType()=="Expression")
    {
        try
        {

            Expression v1=dynamic_cast<Expression&>(expAff.top());
            expMng.removeLitterale(expAff.top());
            expAff.pop();

            Expression res("");// on initialise res a zero


            if (s == "NEG") res = v1.operatorNEG();
            if (s== "DUP")
            {
                res= v1;
                Litterale& l=expMng.addLitterale(res);
                expAff.push(l);
            }
            if (s== "DROP")
            {
                //i++;
                //j = i;
                return;
            }


            if (s == "FORGET")
            {
                Atome resA("");
                if(estUnIdentificateur(v1.getExp()) && !estUnOperateur(v1.getExp()))
                {
                    int ind=chercherAtome(v1.getExp());
                    if( ind == -1)// n'existe pas
                    {
                        expAff.setMessage("L'expression ne correspond pas a un identificateur");
                        Litterale& e=expMng.addLitterale(v1);
                        expAff.push(e);

                    }
                    else // existe
                    {
                        removeAtome(*atomes[ind]);

                    }
                }

                 return;
            }

            if(s == "EVAL")
            {
                QString str;
                int i=0, j=0;
                QString c=v1.getExp();
                while(i < (c.length()))
                {
                    decompCommande(c, i, j);// détermine les i et j pour décomposer la commande reçue à chaque itération de la boucle

                    if(i-j != 0)
                        str = c.mid(j,i-j);
                    else
                        str = c.mid(j, 1);

                    if(estUnIdentificateur(str) && !estUnOperateur(str))
                    {
                        if (chercherAtome(str)== -1)// n'existe pas
                        {
                            expAff.setMessage("Erreur : l'identificateur n'existe pas");
                        }
                        else if (chercherAtome(str)!= -1)// existe
                        {
                            Atome a=dynamic_cast<Atome&>(*atomes[chercherAtome(str)]);
                            if (a.getLitterale().getType()=="Numerique")
                            {
                                Numerique n=dynamic_cast<Numerique&>(a.getLitterale());
                                expAff.push(expMng.addLitterale(n));
                            }
                            else
                            {
                                expAff.setMessage("Erreur : l'identificateur ne pointe pas sur un numerique");
                            }
                        }
                    }
                    else if(estUnOperateurBinaire(str))
                    {

                        j = i;
                        while(i < (c.length()-1) && !estUnOperateur((QString)c[i]) && c[i] != '(' && c[i] != ')')
                        {
                            i++;
                        }
                        if(i == c.length()-1)
                        {
                            i++;
                        }
                        QString str2;
                        if(i-j != 0)
                            str2 = c.mid(j,i-j);
                        else
                            str2 = c.mid(j, 1);
                        if(estUnIdentificateur(str2) && !estUnOperateur(str2))
                        {
                            if (chercherAtome(str2)== -1)// n'existe pas
                            {
                                expAff.setMessage("Erreur : l'identificateur n'existe pas");
                            }
                            else if (chercherAtome(str2)!= -1)// existe
                            {
                                Atome a=dynamic_cast<Atome&>(*atomes[chercherAtome(str2)]);
                                if (a.getLitterale().getType()=="Numerique")
                                {
                                    Numerique n=dynamic_cast<Numerique&>(a.getLitterale());
                                    expAff.push(expMng.addLitterale(n));
                                }
                                else
                                {
                                    expAff.setMessage("Erreur : l'identificateur ne pointe pas sur un numerique");
                                }
                            }
                        }
                        if (expAff.taille() >= 2)
                        {
                            manageBinOpe(beep, str); // Gère toutes les opérations à effectuer avec l'opérateur binaire reçu
                        }// taille>=2
                        else //Manque d'opérandes
                        {
                            expAff.setMessage("Erreur : pas assez d'arguments");
                        }
                    }
                    else if(estUnOperateurUnaire(str))
                    {
                        if (expAff.taille() >= 1)
                        {
                            manageUnOpe(beep, str); // Gère toutes les opérations à effectuer avec l'opérateur unaire reçu
                        }
                        else // Pas d'opérande
                        {
                            expAff.setMessage("Erreur : pas assez d'arguments");
                        }

                    }
                    else if(estUnOperateurSansArg(str))
                    {
                        manageSansArgOpe(beep, str);
                    }

                    else
                    {
                        expAff.setMessage("Erreur : commande inconnue");
                    }
                    j = i;
                }
            }


            if (s == "NOT") res = v1.operatorNOT();
            if(res.getExp()!="")
            {
                Litterale& e=expMng.addLitterale(res);
                expAff.push(e);
            }
        }
        catch(std::bad_cast& e)
        {
            if(beep)
                Beep(500,500);
            expAff.setMessage(e.what());
        }
    }

    else if(expAff.top().getType()=="Programme")
    {
        try
        {

            if(s == "EDIT")
            {
                expAff.edit();
            }
            else
            {
                Programme v1=dynamic_cast<Programme&>(expAff.top());
                expMng.removeLitterale(expAff.top());
                expAff.pop();


                if(s == "EVAL")
                {
                    //commande(v1.getProg(),false);
                    QString str;
                    int i=0, j=0;
                    QString c=v1.getProg();
                    while(i < (c.length()))
                    {
                        decompCommande(c, i, j);// détermine les i et j pour décomposer la commande reçue à chaque itération de la boucle

                        if(i-j != 0)
                            str = c.mid(j,i-j);
                        else
                            str = c.mid(j, 1);


                        if(i < c.length()-1 && estUnRationnel(c, str, i))
                        {
                            getRationnel(str, i, j, c);
                        }

                        else if(estUnEntier(str))
                        {
                            expAff.push(expMng.addLitterale(str.toInt()));
                        }

                        else if(estUnReel(str))
                            expAff.push(expMng.addLitterale(str.toDouble()));

                        else if(estUneExpression(str))
                        {
                            str=str.mid(1,str.length()-2);
                            str = RemoveSpaces(str);
                            expAff.push(expMng.addLitteraleE(str));
                        }
                        else if(estUnProgramme(str))
                        {
                            str=str.mid(1,str.length()-2);
                            expAff.push(expMng.addLitteraleP(str));
                        }
                        else if(estUnOperateurBinaire(str))
                        {
                            if (expAff.taille() >= 2)
                            {
                                manageBinOpe(beep, str); // Gère toutes les opérations à effectuer avec l'opérateur binaire reçu
                            }// taille>=2
                            else //Manque d'opérandes
                            {
                                expAff.setMessage("Erreur : pas assez d'arguments");
                            }

                        }
                        else if(estUnOperateurUnaire(str))
                        {
                            if (expAff.taille() >= 1)
                            {
                                manageUnOpe(beep, str); // Gère toutes les opérations à effectuer avec l'opérateur unaire reçu
                            }
                            else // Pas d'opérande
                            {
                                expAff.setMessage("Erreur : pas assez d'arguments");
                            }

                        }
                        else if(estUnOperateurSansArg(str))
                        {

                            if (str == "CLEAR")
                            {
                                while(!expAff.estVide()) //vide la pile
                                {
                                    expMng.removeLitterale(expAff.top());
                                    expAff.pop();
                                }
                            }
                            if(str == "UNDO")
                            {

                            }

                        }

                        else
                        {
                            expAff.setMessage("Erreur : commande inconnue");
                        }
                        i++;
                        j = i;
                    }
                }
            }
        }
        catch(std::bad_cast& e)
        {
            expAff.setMessage(e.what());
        }
    }
}

void Controleur::manageSansArgOpe(bool beep, QString s/*, int &i, int &j*/)
{
    if (s == "CLEAR")
    {
        while(!expAff.estVide()) //vide la pile
        {
            expMng.removeLitterale(expAff.top());
            expAff.pop();
        }
    }
    if(s == "UNDO" && undo != nullptr)
    {
        undoCommand();
    }
    if(s == "REDO" && redo != nullptr)
    {
        redoCommand();
    }
    if(s == "LASTARGS" && lastArgs != nullptr)
    {
        unsigned int nbArgs;
        if(estUnOperateurBinaire(lastArgs->lastOpe))
            nbArgs = 2;
        else if(estUnOperateurUnaire(lastArgs->lastOpe))
            nbArgs = 1;
        else if(estUnOperateurSansArg(lastArgs->lastOpe))
        {
            if(beep)
                Beep(500,500);
            expAff.setMessage("Erreur: Le dernier opérateur utilisé est sans argument");
        }
        if(nbArgs!=0)
        {
            LitteraleManager::Iterator itL = lastArgs->lm.getIterator();
            unsigned int i = 0;
            while(!itL.isDone())
            {
                i++;
                itL.next();
            }
            itL = lastArgs->lm.getIterator();
            for(unsigned j = 0;j < i-nbArgs;j++)
                itL.next();

            for(Pile::iterator it=lastArgs->p.begin();it!=lastArgs->p.end(), nbArgs != 0; nbArgs--, ++it)
            {
                if(itL.current().getType() == "Numerique")
                    expAff.push(expMng.addLitterale(dynamic_cast<Numerique&>(itL.current())));
                else if(itL.current().getType() == "Expression")
                    expAff.push(expMng.addLitterale(dynamic_cast<Expression&>(itL.current())));
                else if(itL.current().getType() == "Atome")
                    expAff.push(expMng.addLitterale(dynamic_cast<Atome&>(itL.current())));
                else if(itL.current().getType() == "Programme")
                    expAff.push(expMng.addLitterale(dynamic_cast<Programme&>(itL.current())));
                itL.next();
            }
        }
    }
}

void Controleur::undoCommand()
{
    if(lastOpe != "UNDO")
    {
        updateRedo();
        reinstateMemento(undo);
    }
}


void Controleur::redoCommand()
{
    reinstateMemento(redo);
}


void Controleur::updateUndo()
{
    if(undo)
        delete undo;
    undo = new Memento(expMng, expAff, "UNDO");
}

void Controleur::updateRedo()
{
    if(redo)
        delete redo;
    redo = new Memento(expMng, expAff, "REDO");
}

void Controleur::updateLastArgs()
{
    if(lastArgs)
        delete lastArgs;
    lastArgs = new Memento(expMng, expAff, lastOpe);
}


/**
 * \fn void Controleur::updateFile()
 * \brief Met a jour le fichier de restauration
 */
void Controleur::updateFile()
{
    QString texte;
    LitteraleManager::Iterator itL = expMng.getIterator();
    unsigned int nb = 0;
    for(Pile::iterator it=expAff.begin(); it!=expAff.end() && nb<expAff.getNbItems();++it)
    {
        texte += itL.current().toString() + "\n";
        itL.next();
        nb++;
    }
    for(unsigned int i = 0; i < nbAtomes; i++)
    {
        texte += atomes[i]->getLitterale().toString() + " " + atomes[i]->getNom() + " STO\n";
    }

    lastLaunch->open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream flux(lastLaunch);
    flux << texte;

    lastLaunch->close();
}

/**
 * \fn void Controleur::loadFile()
 * \brief Charge le fichier de restauration
 */
void Controleur::loadFile(bool beep)
{
    QString texte;
    if(lastLaunch->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        texte = lastLaunch->readAll();
        lastLaunch->close();
    }
    QString c;
    unsigned int i = 0;
    bool removeTop;
    while(!texte[i].isNull())
    {
        c = "";
        if(texte[i]=='\n')
            i++;
        while(!texte[i].isNull() && texte[i]!='\n')
        {
            c += texte[i];
            i++;
        }
        if(c.contains("STO"))
            removeTop = true;
        commande(c, beep);
        if (removeTop)
        {
            expMng.removeLitterale(expAff.top());
            expAff.pop();
            removeTop = false;
        }
    }
}
void Controleur::initFile()
{
    lastLaunch = new QFile("lastLaunch.txt");
}


void Controleur::commande(const QString& c, bool beepOption)
{
    QString s;
    int i=0, j=0;
    while(i < (c.length()))
    {
        decompCommande(c, i, j); // détermine les i et j pour décomposer la commande reçue à chaque itération de la boucle

        if(i-j != 0)
            s = c.mid(j,i-j);
        else
            s = c.mid(j, 1);
        if(s == "LASTOP")
            s = lastOpe;

        if(estUnOperateur(s))
        {
            lastOpe = s;
            if(s != "UNDO")
            {
                updateUndo();
            }
            if(s != "LASTARGS")
            {
                updateLastArgs();
            }
        }

        if(i < c.length()-1 && estUnRationnel(c, s, i))
        {
            getRationnel(s, i, j, c);
        }

        else if(estUnEntier(s))
        {
            expAff.push(expMng.addLitterale(s.toInt()));
        }

        else if(estUnReel(s))
            expAff.push(expMng.addLitterale(s.toDouble()));

        else if(estUneExpression(s))
        {
            s = s.mid(1,s.length()-2);
            s = RemoveSpaces(s);
            expAff.push(expMng.addLitteraleE(s));
        }
        else if(estUnProgramme(s))
        {
            s = s.mid(1,s.length()-2);
            expAff.push(expMng.addLitteraleP(s));
        }
        else if(estUnIdentificateur(s) && !estUnOperateur(s))
        {
            if (chercherAtome(s)== -1)// n'existe pas
            {
                expAff.push(expMng.addLitteraleE(s));
            }
            else if (chercherAtome(s)!= -1)// existe deja
            {
                Atome a=dynamic_cast<Atome&>(*atomes[chercherAtome(s)]);
                if (a.getLitterale().getType()=="Numerique")
                {
                    Numerique n=dynamic_cast<Numerique&>(a.getLitterale());
                    expAff.push(expMng.addLitterale(n));
                }
                else if (a.getLitterale().getType()=="Programme")
                {
                    Programme p=dynamic_cast<Programme&>(a.getLitterale());
                    expAff.push(expMng.addLitterale(p));
                    manageUnOpe(true, "EVAL");
                }
                else if (a.getLitterale().getType()=="Expression")
                {
                    Expression n=dynamic_cast<Expression&>(a.getLitterale());
                    expAff.push(expMng.addLitterale(n));
                }
            }

        }
        else if(estUnOperateurBinaire(s))
        {
            if (expAff.taille() >= 2)
            {
                manageBinOpe(beepOption, s); // Gère toutes les opérations à effectuer avec l'opérateur binaire reçu
            }// taille>=2
            else //Manque d'opérandes
            {
                if(beepOption)
                    Beep(500,500); // Provoque un bip d'une demi seconde si l'option est activée
                expAff.setMessage("Erreur : pas assez d'arguments");
            }
        }
        else if(estUnOperateurUnaire(s))
        {
            if (expAff.taille() >= 1)
            {
                manageUnOpe(beepOption, s); // Gère toutes les opérations à effectuer avec l'opérateur unaire reçu
            }
            else // Pas d'opérande
            {
                if(beepOption)
                    Beep(500,500);
                expAff.setMessage("Erreur : pas assez d'arguments");
            }
        }
        else if(estUnOperateurSansArg(s))
        {
            manageSansArgOpe(beepOption, s/*, i, j*/);
        }
        else
        {
            if(beepOption)
                Beep(500,500);
            expAff.setMessage("Erreur : commande inconnue");
        }

        i++;
        j = i;

    }

    updateFile();
}
