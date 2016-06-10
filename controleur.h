#ifndef CONTROLEUR
#define CONTROLEUR



class Controleur;

#include "Litterale/Litterale_mng.h"
#include "pile.h"
#include "Litterale/atome.h"
#include "Litterale/numerique.h"
#include "Litterale/programme.h"
#include "Litterale/expression.h"

/**
 *  \class Memento
 *  \brief Implementation du design pattern memento
 *
 * \details Le Memento permet de restaurer un état précédent de la pile (undo/redo) sans violer le principe d'encapsulation.
 */
class Memento
{
  public:

    /**
     * \fn Memento(LitteraleManager& lm1,Pile& p1, QString lo)
     * \brief Constructeur
     */
    Memento(LitteraleManager& lm1,Pile& p1, QString lo): lm(*(new LitteraleManager)), p(*(new Pile))
    {
        p.setNbItemsToAffiche(p1.getNbItemsToAffiche());
        lastOpe = lo;
        LitteraleManager::Iterator itL = lm1.getIterator();
        unsigned int nb = 0;
        for(Pile::iterator it=p1.begin(); it!=p1.end() && nb<p1.getNbItems();++it)
        {
            if(itL.current().getType() == "Numerique")
                p.push(lm.addLitterale(dynamic_cast<Numerique&>(itL.current())));
            else if(itL.current().getType() == "Expression")
                p.push(lm.addLitterale(dynamic_cast<Expression&>(itL.current())));
            else if(itL.current().getType() == "Atome")
                p.push(lm.addLitterale(dynamic_cast<Atome&>(itL.current())));
            else if(itL.current().getType() == "Programme")
                p.push(lm.addLitterale(dynamic_cast<Programme&>(itL.current())));
            itL.next();
            nb++;
        }
    }

    /**
     * \fn void setLastOpe(QString lo)
     * \brief Accesseur en ecriture de l'attribut lastope (dernier operateur applique)
     */
    void setLastOpe(QString lo) {lastOpe = lo;}
  private:
    friend class Controleur;
    LitteraleManager& lm;
    Pile& p;
    QString lastOpe;
};

/**
 *  \class Controleur
 *  \brief Interface avec l'utilisateur et gestion des identificateurs entres par l'utilisateur
 */
class Controleur
{
    LitteraleManager& expMng;
    Pile& expAff;
    QString lastOpe;
    //Memento
    Memento* undo;
    Memento* redo;
    Memento* lastArgs;
    // tableau pour maj et sauvegarde des atomes
    Atome** atomes;
    unsigned int nbAtomes;
    unsigned int nbAtomesMax;
    void agrandissementCapacite();

public:
    /**
     * \fn unsigned int getNbAtomes()
     * \brief Accesseur en lecture de l'attribut nbAtome
     */
    unsigned int getNbAtomes(){return nbAtomes;}
    /**
     * \fn Atome** getAtomes()
     * \brief Accesseur en lecture de l'attribut atomes
     */
    Atome** getAtomes() {return atomes;}

    /**
     * \fn Atome& addAtome(Atome v)
     * \brief Ajout de l'atome passe en argument
     */
    Atome& addAtome(Atome v)
    {
        if (nbAtomes==nbAtomesMax) agrandissementCapacite();
        atomes[nbAtomes++]=new Atome(v);// appel au constructeur de recopie
        return *atomes[nbAtomes-1];
    }
    void removeAtome(Atome& e);

    int chercherAtome(QString s);

    /**
     * \fn Atome& operator[](int i)
     * \brief Operateur []
     */
    Atome& operator[](int i){return *atomes[i];}

    /**
     * \fn Controleur(LitteraleManager& m, Pile& v)
     * \brief Constructeur
     */
    Controleur(LitteraleManager& m, Pile& v):expMng(m), expAff(v),lastOpe(""),
        undo(nullptr), redo(nullptr), lastArgs(nullptr),nbAtomes(0),nbAtomesMax(0), atomes(nullptr){}
    void commande(const QString& c, bool beep);

    void undoCommand();
    void redoCommand();
    void lastArgsCommand();

    void updateUndo();
    void updateRedo();
    void updateLastArgs();

    void getRationnel(QString s, int &i, int &j, const QString& c);

    void manageBinOpe(bool beep, QString s);
    void manageUnOpe(bool beep, QString s);
    void manageSansArgOpe(bool beep, QString s);

    Numerique manageNumOpeNumAndNum(Numerique v1, Numerique v2, QString s, Numerique res, bool beep);
    Numerique manageLogicOpeNumAndNum(Numerique v1, Numerique v2, QString s, Numerique res, bool beep);
    //Numerique managePileOpeNumAndNum(Numerique v1, Numerique v2,QString s, Numerique res);
    Expression manageNumOpeNumAndExpr(Expression v1, Expression v2E, QString s, Expression res);
    Expression manageLogicOpeNumAndExpr(Expression v1, Expression v2E, QString s, Expression res);
    //Expression managePileOpeNumAndExpr(Expression v1, Numerique v2, QString s, Expression res);
    Expression manageNumOpeExprAndExpr(Expression v1, Expression v2E, QString s, Expression res);
    Expression manageLogicOpeExprAndExpr(Expression v1, Expression v2E, QString s, Expression res);
    //Expression managePileOpeExprAndExpr(Expression v1, Expression v2,QString s, Expression res);
    Expression manageNumOpeExprAndNum(Expression v1, Expression v2E,QString s, Expression res);
    Expression manageLogicOpeExprAndNum(Expression v1, Expression v2E,QString s, Expression res);
    //Numerique managePileOpeExprAndNum(Numerique v1, Expression v2,QString s, Numerique res);

    Atome manageAtomeOpeNumAndExpr(Numerique v1, Expression v2,QString s, Atome res);
    Atome manageAtomeOpeExprAndExpr(Expression v1, Expression v2,QString s, Atome res);
    Atome manageAtomeOpePrgmAndExpr (Programme v1, Expression v2,QString s, Atome res);

    template<class T1, class T2>
    T1 managePileOpeT2AndT1(T1 v1, T2 v2,QString s, T1 res);

    /**
     * \fn Memento *createMemento()
     * \brief Cree un nouveau Memento
     */
    Memento *createMemento()
    {
        return new Memento(expMng, expAff,lastOpe);
    }

    /**
     * \fn void reinstateMemento(Memento *mem)
     * \brief Retabli le Memento
     */
    void reinstateMemento(Memento *mem)
    {
        expAff.setNbItemsToAffiche(mem->p.getNbItemsToAffiche());
        lastOpe = mem->lastOpe;

        while(!expAff.estVide())
        {
            expMng.removeLitterale(expAff.top());
            expAff.pop();
        }
        LitteraleManager::Iterator itL = mem->lm.getIterator();
        unsigned int nb=0;
        for(Pile::iterator it=mem->p.begin(); it!=mem->p.end() && nb<mem->p.getNbItemsToAffiche();++it)
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
            nb++;
        }
    }
};


/**
 * \fn template<class T1, class T2> T1 Controleur::managePileOpeT2AndT1(T1 v1, T2 v2,QString s, T1 res)
 * \brief Patron de fonction pour realiser less operations de pile.
 *
 * \param v1 Deuxieme argument depile
 * \param v2 Premier argument depile
 * \param s QString qui represente l'operateur a appliquer
 * \param res resultat de l'operation
 * \return La fonction retourne le resultat de l'operation qui sera empile par la suite.
 */

template<class T1, class T2>
T1 Controleur::managePileOpeT2AndT1(T1 v1, T2 v2,QString s, T1 res)
{

    if (s == "SWAP")
    {
        res=v1;
        Litterale& l=expMng.addLitterale(v2);

        expAff.push(l);

    }
    return res;
}


#endif // CONTROLEUR

