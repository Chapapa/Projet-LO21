#ifndef _COMPUTER_H
#define _COMPUTER_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
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
    QString typeRe;
    QString typeIm;
    friend class LitteraleManager;
public:
    Litterale (const QString tr,const QString ti):typeRe(tr),typeIm(ti){}
    QString getTypeRe() const {return typeRe;}
    QString getTypeIm() const {return typeIm;}
    void setTypeRe(QString s){typeRe=s;}
    void setTypeIm(QString s){typeIm=s;}

    virtual QString toString()const=0;
    virtual double getValue() const=0;
};


class Numerique : public Litterale
{
    double numReel;
    int denomReel;
    double numIm;
    int denomIm;

    void simplificationRe();// simplifier les rationels
    void simplificationIm();


    friend class LitteraleManager;
public:

    Numerique(int v,QString tr="entier"):numReel(v),denomReel(1),numIm(0),denomIm(1),Litterale(tr,"null"){}
    Numerique(double v,QString tr="reel"):numReel(v),denomReel(1),numIm(0),denomIm(1), Litterale(tr,"null"){}
    Numerique(int v1, int v2,QString tr="rationnel"):numIm(0),denomIm(1), Litterale(tr,"null"){ setRationnelRe(v1,v2);}
    Numerique(double v1,double v3,QString tr,QString ti, double v2=1, double v4=1):Litterale(tr,ti)
    {
        if (tr=="rationnel")setRationnelRe(v1,v2);
        if (ti=="rationnel")setRationnelIm(v3,v4);
    }

    Numerique(const Numerique& e);
    Numerique& operator=(const Numerique& e);
    QString toString() const;

    double getValue() const {return numReel;} // Ã  modifier pour considérer tous les cas

    void setRationnelRe(int n,int d);// exception si denominateur a 0
    void setRationnelIm(int n,int d);


    QString getResTypeRe(const Numerique& n, double dr);
    QString getResTypeIm(const Numerique& n, double ni, double di);


    Numerique operator+(const Numerique& n)
    {
            double nr=(numReel*n.denomReel + n.numReel*denomReel);
            int dr=denomReel*n.denomReel;
            double ni=(numIm*n.denomIm+n.numIm*denomIm);
            int di=denomIm*n.denomIm;

            QString tRe=getResTypeRe(n,dr);
            QString tIm=getResTypeIm(n,ni,di);

           Numerique res(nr,ni,tRe,tIm,dr,di);

            return res;
    }

    Numerique operator-(const Numerique& n)
    {

        double nr=(numReel*n.denomReel-n.numReel*denomReel);
        int dr=denomReel*n.denomReel;
        double ni=(numIm*n.denomIm-n.numIm*denomIm);
        int di=denomIm*n.denomIm;

        QString tRe=getResTypeRe(n,dr);
        QString tIm=getResTypeIm(n,ni,di);

        Numerique res(nr,ni,tRe,tIm,dr,di);

        return res;
    }

    //pas encore implementés
    Numerique operator*(const Numerique& n);
    Numerique operator/(const Numerique& n);
    Numerique operator$(const Numerique& n);
};



class LitteraleManager
{
    Litterale** exps;
    unsigned int nb;
    unsigned int nbMax;
    void agrandissementCapacite();
    LitteraleManager():exps(nullptr),nb(0),nbMax(0){}
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
    Litterale& addLitterale(int v);
    Litterale& addLitterale(double v);
    void removeLitterale(Litterale& e);
    static LitteraleManager& getInstance();
    static void libererInstance();
    class Iterator
    {
        friend class LitteraleManager;
        Litterale** currentExp;
        unsigned int nbRemain;
        Iterator(Litterale** u, unsigned nb):currentExp(u),nbRemain(nb){}
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
    void push(Litterale& e);
    void pop();
    bool estVide() const { return nb==0; }
    unsigned int taille() const { return nb; }
    void affiche(QTextStream& f) const;
    Litterale& top() const;
    void setNbItemsToAffiche(unsigned int n) { nb=n; }
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
};

class Controleur
{
    LitteraleManager& expMng;
    Pile& expAff;
public:
    Controleur(LitteraleManager& m, Pile& v):expMng(m), expAff(v){}
    void commande(const QString& c);

};

bool estUnOperateur(const QString s);
bool estUnNombre(const QString s);


#endif
