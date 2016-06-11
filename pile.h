#ifndef PILE
#define PILE

class Litterale;
#include "computer.h"
#include "item.h"
#include "Litterale/litterale.h"


/**
 *  \class Pile
 *  \brief Gestion de la pile
 *
 * \details La pile est indispensable a l'evaluation d'une formule ecrite en RPN.
 *  La classe pile est chargé de la gestion de la pile d’affichage des litterales. Elle emet aussi des messages destinés à l’utilisateur.
 */

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
    /**
     * \fn Pile()
     * \brief Constructeur
     */
    Pile():items(nullptr),nb(0),nbMax(0),message(""),nbAffiche(4){}
    ~Pile();

    /**
     * \fn void setNbItems(unsigned int n)
     * \brief Accesseur en ecriture pour l'attribut nb
     */
    void setNbItems(unsigned int n) {nb = n;}

    /**
     * \fn unsigned int getNbItems()
     * \brief Accesseur en lecture pour l'attribut nb
     */
    unsigned int getNbItems() {return nb;}

    void push(Litterale& e);
    void pop();

    /**
     * \fn bool estVide()
     * \brief Teste si la pile est vide
     */
    bool estVide() const { return nb==0; }

    /**
     * \fn unsigned int taille() const
     * \brief Retourne la taille de la pile
     */
    unsigned int taille() const { return nb; }
    void affiche(QTextStream& f) const;
    Litterale& top() const;

    /**
     * \fn void setNbItemsToAffiche(unsigned int n)
     * \brief Accesseur en ecriture pour l'attribut nbAffiche(nombre d'items a afficher)
     */
    void setNbItemsToAffiche(unsigned int n) { nbAffiche=n; }

    /**
     * \fn unsigned int getNbItemsToAffiche() const
     * \brief Accesseur en lecture pour l'attribut nbAffiche(nombre d'items a afficher)
     */
    unsigned int getNbItemsToAffiche() const { return nbAffiche; }

    /**
     * \fn void setMessage(const QString& m)
     * \brief Accesseur en ecriture pour l'attribut message
     */
    void setMessage(const QString& m) { message=m; modificationEtat(); }

    /**
     * \fn QString getMessage() const
     * \brief Accesseur en lecture pour l'attribut message
     */
    QString getMessage() const { return message; }

    /**
     *  \class iterator
     *  \brief Design pattern iterator pour la classe pile
     */
    class iterator
    {
        Item* current;

        /**
         * \fn iterator(Item* u)
         * \brief Constructeur de la classe Iterator
         */
        iterator(Item* u):current(u){}
        friend class Pile;
    public:

        /**
         * \fn iterator()
         * \brief Constructeur sans arguments de la classe Iterator
         */
        iterator():current(nullptr){}

        /**
         * \fn Litterale& operator*() const
         * \brief Retourne la valeur de l'element courrant
         */
        Litterale& operator*() const { return current->getLitterale(); }

        /**
         * \fn bool operator!=(iterator it) const
         * \brief Operateur !=
         */
        bool operator!=(iterator it) const { return current!=it.current; }

        /**
         * \fn iterator& operator++()
         * \brief Operateur ++ prefixe
         */
        iterator& operator++(){ --current; return *this; }
    };

    /**
     * \fn iterator begin()
     * \brief Retourne un iterator sur le premier element
     */
    iterator begin() { return iterator(items+nb-1); }

    /**
    * \fn iterator end()
    * \brief Retourne un iterator sur le dernier element
    */
    iterator end() { return iterator(items-1); }

    /**
     *  \class const_iterator
     *  \brief Design pattern const_iterator pour la classe pile
     */
    class const_iterator
    {
        Item* current;


        /**
         * \fn iterator(Item* u)
         * \brief Constructeur de la classe Iterator
         */
        const_iterator(Item* u):current(u){}
        friend class Pile;
    public:
        /**
         * \fn iterator()
         * \brief Constructeur sans arguments de la classe Iterator
         */
        const_iterator():current(nullptr){}

        /**
         * \fn Litterale& operator*() const
         * \brief Retourne la valeur de l'element courrant
         */
        const Litterale& operator*() const { return current->getLitterale(); }

        /**
         * \fn bool operator!=(iterator it) const
         * \brief Operateur !=
         */
        bool operator!=(const_iterator it) const { return current!=it.current; }

        /**
         * \fn const_iterator& operator++()
         * \brief Operateur ++ prefixe
         */
        const_iterator& operator++(){ --current; return *this; }
    };

    /**
     * \fn const_iterator begin() const
     * \brief Retourne un iterator sur le premier element
     */
    const_iterator begin() const { return const_iterator(items+nb-1); }

    /**
    * \fn const_iterator end()const
    * \brief Retourne un iterator sur le dernier element
    */
    const_iterator end() const { return const_iterator(items-1); }

signals:
    void modificationEtat();
    void edit();
    void atomeAdded();
    void atomeRemoved();
};

#endif // PILE

