#ifndef LITTERALE_MNG
#define LITTERALE_MNG

#include "litterale.h"
#include "computer.h"

/**
 *  \class LitteraleManager
 *  \brief Responsable de la creation et de la destruction des litterales
 *
 * \details Le LitteraleManager est un singleton. Il contient un tableau de pointeur de Litterale.
 */
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


#endif // LITTERALE_MNG

