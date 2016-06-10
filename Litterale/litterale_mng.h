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

    /**
     *  \class Handler
     *  \brief Design pattern singleton pour la classe LitteraleManager
     */
    struct Handler
    {
        LitteraleManager* instance;
        /**
         * \fn Handler()
         * \brief Constructeur de la classe Handler
         */
        Handler():instance(nullptr){}
        // destructeur appelé à la fin du programme
        /**
         * \fn ~Handler()
         * \brief Destructeur de la classe Handler
         */
        ~Handler(){ delete instance; }
    };
    static Handler handler;
public:
    /**
     * \fn LitteraleManager()
     * \brief Constructeur de la classe LitteraleManager
     */
    LitteraleManager():exps(nullptr),nb(0),nbMax(0){}
    Litterale& addLitteraleE(QString v);
    Litterale& addLitteraleP(QString v);
    Litterale& addLitteraleA(QString v);
    Litterale& addLitterale(int v);
    Litterale& addLitterale(double v);

    /**
     * \fn template <class T> Litterale& addLitterale(T v)
     * \brief Template pour l'ajout d'une litterale
     */
    template <class T>
    Litterale& addLitterale(T v)

    {
        if (nb==nbMax) agrandissementCapacite();
        exps[nb++]=new T(v);// appel au constructeur de recopie
        return *exps[nb-1];
    }

    void removeLitterale(Litterale& e);
    static void libererInstance();

    /**
     *  \class Iterator
     *  \brief Design pattern iterator pour la classe LitteraleManager
     */
    class Iterator
    {
        friend class LitteraleManager;
        Litterale** currentExp;
        unsigned int nbRemain;
        unsigned int start;

        /**
         * \fn Iterator(Litterale** u, unsigned nb)
         * \brief Constructeur de la classe Iterator
         */
        Iterator(Litterale** u, unsigned nb):currentExp(u),nbRemain(nb), start(nb){}
    public:

        /**
         * \fn Iterator()
         * \brief Constructeur sans arguments de la classe Iterator
         */
        Iterator():currentExp(nullptr),nbRemain(0){}

        /**
         * \fn bool isDone()
         * \brief Indique la fin du parcours
         */
        bool isDone() const { return nbRemain==0; }

        /**
         * \fn void next()
         * \brief Avance d'un element
         */
        void next()
        {
            if (isDone())
                throw ComputerException("error, next on an iterator which is done");
            nbRemain--;
            currentExp++;
        }

        /**
         * \fn previous()
         * \brief Recule d'un element
         */
        void previous()
        {
            if (nbRemain == start)
                throw ComputerException("error, previous on an iterator which is at start");
            nbRemain++;
            currentExp--;
        }

        /**
         * \fn Litterale& current() const
         * \brief Retourne la valeur de l'element courrant
         */
        Litterale& current() const
        {
            if (isDone())
                throw ComputerException("error, indirection on an iterator which is done");
            return **currentExp;
        }
    };
    /**
     * \fn Iterator getIterator()
     * \brief Retourne un iterator sur le premier element
     */
    Iterator getIterator()
    {
        return Iterator(exps,nb);
    }

    /**
     *  \class iterator
     *  \brief Design pattern iterator pour la classe LitteraleManager
     */
    class iterator
    {
        Litterale** current;
        /**
         * \fn iterator(Litterale** u)
         * \brief Constructeur de la classe Iterator
         */
        iterator(Litterale** u):current(u){}
        friend class LitteraleManager;
    public:
        /**
         * \fn iterator()
         * \brief Constructeur sans arguments de la classe Iterator
         */
        iterator():current(0){}
        /**
         * \fn Litterale& operator*() const
         * \brief Retourne la valeur de l'element courrant
         */
        Litterale& operator*() const { return **current; }

        /**
         * \fn bool operator!=(iterator it) const
         * \brief Operateur !=
         */
        bool operator!=(iterator it) const { return current!=it.current; }

        /**
         * \fn iterator& operator++()
         * \brief Operateur ++ prefixe
         */
        iterator& operator++(){ ++current; return *this; }
    };

    /**
     * \fn iterator begin()
     * \brief Retourne un iterator sur le premier element
     */
    iterator begin() { return iterator(exps); }

    /**
     * \fn iterator end()
     * \brief Retourne un iterator sur le dernier element
     */
    iterator end() { return iterator(exps+nb); }

    /**
     *  \class const_iterator
     *  \brief Design pattern iterator pour la classe LitteraleManager
     */
    class const_iterator
    {
        Litterale** current;

        /**
         * \fn const_iterator(Litterale** u)
         * \brief Constructeur de la classe const_iterator
         */
        const_iterator(Litterale** u):current(u){}
        friend class LitteraleManager;
    public:

        /**
         * \fn const_iterator()
         * \brief Constructeur sans arguments de la classe const_iterator
         */
        const_iterator():current(0){}

        /**
         * \fn Litterale& operator*() const
         * \brief Retourne la valeur de l'element courrant
         */
        Litterale& operator*() const { return **current; }

        /**
         * \fn bool operator!=(iterator it) const
         * \brief Operateur !=
         */
        bool operator!=(const_iterator it) const { return current!=it.current; }

        /**
         * \fn const_iterator& operator++()
         * \brief Operateur ++ prefixe
         */
        const_iterator& operator++(){ ++current; return *this; }
    };

    /**
     * \fn const_iterator begin() const
     * \brief Retourne un iterator sur le premier element
     */
    const_iterator begin() const { return const_iterator(exps); }

    /**
     * \fn const_iterator end() const
     * \brief Retourne un iterator sur le dernier element
     */
    const_iterator end() const { return const_iterator(exps+nb); }
};


#endif // LITTERALE_MNG

