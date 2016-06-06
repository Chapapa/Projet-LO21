#ifndef _COMPUTER_H
#define _COMPUTER_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include <windows.h>
using namespace std;

class ComputerException
{
    QString info;
public:
    ComputerException(const QString& str):info(str){}
    QString getInfo() const { return info; }
};


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


// gestion espace tabulation retour chariot non faite
// pour EVAL ne pas mettre d'espace apres [ et avant ]
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
    QString toString()const {
        QString res=nom;
        return res;
    }

};


class Expression : public Litterale
{
    QString exp;
public :
    Expression(QString e):exp(e),Litterale("Expression"){}
    QString getExp() const{return exp;}
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



class Numerique : public Litterale
{
    double numReel;
    int denomReel;
    double numIm;
    int denomIm;
    QString typeRe;
    QString typeIm;

    void simplificationRe();// simplifier les rationnels
    void simplificationIm();


    friend class LitteraleManager;
public:
    QString getTypeRe() const {return typeRe;}
    QString getTypeIm() const {return typeIm;}
    void setTypeRe(QString s){typeRe=s;}
    void setTypeIm(QString s){typeIm=s;}
    double getNumReel()const {return numReel;}
    double getNumIm()const {return numIm;}
    int getDenomReel()const {return denomReel;}
    int getDenomIm()const {return denomIm;}

    Numerique(int v,QString tr="entier"):numReel(v),denomReel(1),numIm(0),denomIm(1),typeRe(tr), typeIm("null"),Litterale("Numerique"){}
    Numerique(double v,QString tr="reel"):numReel(v),denomReel(1),numIm(0),denomIm(1),typeRe(tr), typeIm("null"),Litterale("Numerique"){}
    Numerique(int v1, int v2,QString tr="rationnel"):numIm(0),denomIm(1), typeRe(tr), typeIm("null"),Litterale("Numerique") {setRationnelRe(v1,v2);}
    Numerique(double v1,double v3,QString tr,QString ti, double v2=1, double v4=1):typeRe(tr),typeIm(ti),Litterale("Numerique")
    {
        if (typeRe=="rationnel")setRationnelRe(v1,v2);
        else
        {
            numReel=v1;
            denomReel=1;
        }
        if (typeIm=="rationnel")setRationnelIm(v3,v4);
        else
        {
            numIm=v3;
            denomIm=1;
        }
    }
    //pas besoin, ceux par defaut devraient marcher
    /*Numerique(const Numerique& e);
    Numerique& operator=(const Numerique& e);*/
    QString toString() const;

    double getValue() const {return numReel;}

    void setRationnelRe(int n,int d);// exception si denominateur a 0
    void setRationnelIm(int n,int d);


    //QString getResTypeRe(const Numerique& n, int dr);
    QString getResTypeRe(double nr, int dr);
    QString getResTypeIm(double ni, int di);


    Numerique operator+(const Numerique& n);
    Numerique operator-(const Numerique& n);
    Numerique operator*(const Numerique& n);
    Numerique operator/(const Numerique& n);
    Numerique operator$(const Numerique& n);
    Numerique operatorDIV(const Numerique& n);
    Numerique operatorMOD(const Numerique& n);
    Numerique operatorNEG();
    Numerique operatorNUM();
    Numerique operatorDEN();
    Numerique operatorRE();
    Numerique operatorIM();
    Numerique operator==(const Numerique& n);
    Numerique operator!=(const Numerique& n);
    Numerique operator>=(const Numerique& n);
    Numerique operator<=(const Numerique& n);
    Numerique operator<(const Numerique& n);
    Numerique operator>(const Numerique& n);
    Numerique operatorAND(const Numerique& n);
    Numerique operatorOR(const Numerique& n);
    Numerique operatorNOT();
};






class Item
{
    Litterale* exp;
public:
    Item():exp(nullptr){}
    void setLitterale(Litterale& e) { exp=&e; }
    void raz() { exp=0; }
    Litterale& getLitterale() const;
};

class Pile : public QObject
{
    Q_OBJECT

    Item* items;
    unsigned int nb;
    unsigned int nbMax;
    QString message;
    void agrandissementCapacite();
    unsigned int nbAffiche;
public:
    Pile():items(nullptr),nb(0),nbMax(0),message(""),nbAffiche(4){}
    ~Pile();

    void setNbItems(unsigned int n) {nb = n;}
    unsigned int getNbItems() {return nb;}

    void push(Litterale& e);
    void pop();
    bool estVide() const { return nb==0; }
    unsigned int taille() const { return nb; }
    void affiche(QTextStream& f) const;
    Litterale& top() const;

    void setNbItemsToAffiche(unsigned int n) { nbAffiche=n; }
    unsigned int getNbItemsToAffiche() const { return nbAffiche; }

    void setMessage(const QString& m) { message=m; modificationEtat(); }
    QString getMessage() const { return message; }

    class iterator
    {
        Item* current;
        iterator(Item* u):current(u){}
        friend class Pile;
    public:
        iterator():current(nullptr){}
        Litterale& operator*() const { return current->getLitterale(); }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ --current; return *this; }
    };
    iterator begin() { return iterator(items+nb-1); }
    iterator end() { return iterator(items-1); }

    class const_iterator
    {
        Item* current;
        const_iterator(Item* u):current(u){}
        friend class Pile;
    public:
        const_iterator():current(nullptr){}
        const Litterale& operator*() const { return current->getLitterale(); }
        bool operator!=(const_iterator it) const { return current!=it.current; }
        const_iterator& operator++(){ --current; return *this; }
    };
    const_iterator begin() const { return const_iterator(items+nb-1); }
    const_iterator end() const { return const_iterator(items-1); }

signals:
    void modificationEtat();
    void edit();
    void atomeAdded();
};

class LitteraleManager
{
    Litterale** exps;
    unsigned int nb;
    unsigned int nbMax;
    void agrandissementCapacite();

    ~LitteraleManager();
    LitteraleManager(const LitteraleManager& m);
    LitteraleManager& operator=(const LitteraleManager& m);

    struct Handler
    {
        LitteraleManager* instance;
        Handler():instance(nullptr){}
        // destructeur appelé à la fin du programme
        ~Handler(){ delete instance; }
    };
    static Handler handler;
public:
    LitteraleManager():exps(nullptr),nb(0),nbMax(0){}
    Litterale& addLitteraleE(QString v);
    Litterale& addLitteraleP(QString v);
    Litterale& addLitteraleA(QString v);
    Litterale& addLitterale(int v);
    Litterale& addLitterale(double v);
    template <class T>
    Litterale& addLitterale(T v)

    {
        if (nb==nbMax) agrandissementCapacite();
        exps[nb++]=new T(v);// appel au constructeur de recopie
        return *exps[nb-1];
    }

    void removeLitterale(Litterale& e);
    static void libererInstance();

    class Iterator
    {
        friend class LitteraleManager;
        Litterale** currentExp;
        unsigned int nbRemain;
        unsigned int start;
        Iterator(Litterale** u, unsigned nb):currentExp(u),nbRemain(nb), start(nb){}
    public:
        Iterator():currentExp(nullptr),nbRemain(0){}
        bool isDone() const { return nbRemain==0; }
        void next()
        {
            if (isDone())
                throw ComputerException("error, next on an iterator which is done");
            nbRemain--;
            currentExp++;
        }
        void previous()
        {
            if (nbRemain == start)
                throw ComputerException("error, previous on an iterator which is at start");
            nbRemain++;
            currentExp--;
        }
        Litterale& current() const
        {
            if (isDone())
                throw ComputerException("error, indirection on an iterator which is done");
            return **currentExp;
        }
    };
    Iterator getIterator()
    {
        return Iterator(exps,nb);
    }
    class iterator
    {
        Litterale** current;
        iterator(Litterale** u):current(u){}
        friend class LitteraleManager;
    public:
        iterator():current(0){}
        Litterale& operator*() const { return **current; }
        bool operator!=(iterator it) const { return current!=it.current; }
        iterator& operator++(){ ++current; return *this; }
    };
    iterator begin() { return iterator(exps); }
    iterator end() { return iterator(exps+nb); }

    class const_iterator
    {
        Litterale** current;
        const_iterator(Litterale** u):current(u){}
        friend class LitteraleManager;
    public:
        const_iterator():current(0){}
        Litterale& operator*() const { return **current; }
        bool operator!=(const_iterator it) const { return current!=it.current; }
        const_iterator& operator++(){ ++current; return *this; }
    };
    const_iterator begin() const { return const_iterator(exps); }
    const_iterator end() const { return const_iterator(exps+nb); }
};

class Controleur;

class Memento
{
  public:
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

  private:
    friend class Controleur;
    LitteraleManager& lm;
    Pile& p;
    QString lastOpe;
};

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
    Atome ** atomes;
    unsigned int nbAtomes;
    unsigned int nbAtomesMax;
    void agrandissementCapacite();

public:

    unsigned int getNbAtomes(){return nbAtomes;}
   /*~Controleur();*/
    Atome** getAtomes() {return atomes;}
    Atome& addAtome(Atome v)
    {
        if (nbAtomes==nbAtomesMax) agrandissementCapacite();
        atomes[nbAtomes++]=new Atome(v);// appel au constructeur de recopie
        return *atomes[nbAtomes-1];
    }
    void removeAtome(Atome& e);

    int chercherAtome(QString s);
    Atome& operator[](int i){return *atomes[i];}

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

    void manageBinOpe(bool beep, QString s, int &i, int &j);
    void manageUnOpe(bool beep, QString s, int &i, int &j);
    void manageSansArgOpe(bool beep, QString s/*, int &i, int &j*/);

    Numerique manageNumOpeNumAndNum(Numerique v1, Numerique v2, QString s, Numerique res, bool beep);
    Numerique manageLogicOpeNumAndNum(Numerique v1, Numerique v2, QString s, Numerique res, bool beep);
    Numerique managePileOpeNumAndNum(Numerique v1, Numerique v2,QString s, Numerique res);
    Expression manageNumOpeNumAndExpr(Expression v1, Expression v2E, QString s, Expression res);
    Expression manageLogicOpeNumAndExpr(Expression v1, Expression v2E, QString s, Expression res);
    Expression managePileOpeNumAndExpr(Expression v1, Numerique v2, QString s, Expression res);
    Expression manageNumOpeExprAndExpr(Expression v1, Expression v2E, QString s, Expression res);
    Expression manageLogicOpeExprAndExpr(Expression v1, Expression v2E, QString s, Expression res);
    Expression managePileOpeExprAndExpr(Expression v1, Expression v2,QString s, Expression res);
    Expression manageNumOpeExprAndNum(Expression v1, Expression v2E,QString s, Expression res);
    Expression manageLogicOpeExprAndNum(Expression v1, Expression v2E,QString s, Expression res);
    Numerique managePileOpeExprAndNum(Numerique v1, Expression v2,QString s, Numerique res);

    Atome manageAtomeOpeNumAndExpr(Numerique v1, Expression v2,QString s, Atome res);
    Atome manageAtomeOpeExprAndExpr(Expression v1, Expression v2,QString s, Atome res);
    Atome manageAtomeOpePrgmAndExpr (Programme v1, Expression v2,QString s, Atome res);

    template<class T1, class T2>
    T1 managePileOpeT2AndT1(T1 v1, T2 v2,QString s, T1 res);

    Memento *createMemento()
    {
        return new Memento(expMng, expAff,lastOpe);
    }
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


bool estUnOperateur(const QString s);
bool estUnOperateurBinaire(const QString s);
bool estUnOperateurUnaire(const QString s);
bool estUnNombre(const QString s);
bool estUneExpression(const QString s);
bool estUnProgramme(QString s);
bool estUnOperateurSansArg(const QString s);
bool estUnIndentificateur(const Expression& e);


template<class T1, class T2>
T1 Controleur::managePileOpeT2AndT1(T1 v1, T2 v2,QString s, T1 res)
{
    /*if (s == "SWAP")
    {
        res=v1;
        Litterale& l=expMng.addLitterale(v2);
        expAff.push(l);

        Litterale& e=expMng.addLitterale(res);
        expAff.push(e);


    }
    return res;*/
    if (s == "SWAP")
    {
        res=v1;
        Litterale& l=expMng.addLitterale(v2);

        expAff.push(l);

    }
    return res;
}

#endif
