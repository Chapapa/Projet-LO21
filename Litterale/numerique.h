#ifndef NUMERIQUE
#define NUMERIQUE

#include "computer.h"
#include "litterale.h"

/**
 *  \class Numerique
 *  \brief Gestion des Numeriques
 *
 * \details La classe Numerique herite de la classe Litterale. Elle gère la manipulation des nombres réels,rationnels, complexes et entiers.
 */

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
    /**
     * \fn QString getTypeRe() const
     * \brief Accesseur en lecture de l'attribut typeRe
     */
    QString getTypeRe() const {return typeRe;}

    /**
     * \fn QString getTypeIm()
     * \brief Accesseur en lecture de l'attribut typeIm
     */
    QString getTypeIm() const {return typeIm;}

    /**
     * \fn void setTypeRe(QString s)
     * \brief Accesseur en ecriture de l'attribut typeRe
     */
    void setTypeRe(QString s){typeRe=s;}

    /**
     * \fn void setTypeIm(QString s)
     * \brief Accesseur en ecriture de l'attribut typeIm
     */
    void setTypeIm(QString s){typeIm=s;}

    /**
     * \fn double getNumReel()const
     * \brief Accesseur en lecture de l'attribut numReel
     */
    double getNumReel()const {return numReel;}

    /**
     * \fn double getNumIm()const
     * \brief Accesseur en lecture de l'attribut numIm
     */
    double getNumIm()const {return numIm;}

    /**
     * \fn int getDenomReel()const
     * \brief Accesseur en lecture de l'attribut denomReel
     */
    int getDenomReel()const {return denomReel;}

    /**
     * \fn int getDenomIm()const
     * \brief Accesseur en lecture de l'attribut denomIm
     */
    int getDenomIm()const {return denomIm;}


    /**
     * \fn Numerique(int v,QString tr="entier")
     * \brief Constructeur
     * \param v Numerateur reel
     * \param tr type de la partie reelle
     */
    Numerique(int v,QString tr="entier"):numReel(v),denomReel(1),numIm(0),denomIm(1),typeRe(tr), typeIm("null"),Litterale("Numerique"){}

    /**
     * \fn Numerique(double v,QString tr="reel")
     * \brief Constructeur
     * \param v Numerateur reel
     * \param tr type de la partie reelle
     */
    Numerique(double v,QString tr="reel"):numReel(v),denomReel(1),numIm(0),denomIm(1),typeRe(tr), typeIm("null"),Litterale("Numerique"){}

    /**
     * \fn Numerique(int v1, int v2,QString tr="rationnel")
     * \brief Constructeur
     * \param v1 Numerateur reel
     * \param v2 Denominateur reel
     * \param tr type de la partie reelle
     */
    Numerique(int v1, int v2,QString tr="rationnel"):numIm(0),denomIm(1), typeRe(tr), typeIm("null"),Litterale("Numerique") {setRationnelRe(v1,v2);}

    /**
     * \fn Numerique(double v1,double v3,QString tr,QString ti, double v2=1, double v4=1)
     * \brief Constructeur
     * \param v1 Numerateur reel
     * \param v3 Numerateur imaginaire
     * \param tr type de la partie reelle
     * \param ti type de la partie imaginaire
     * \param v2 Denominateur reel
     * \param v4 Denominateur imaginaire
     */
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

    QString toString() const;

    /**
     * \fn double getValue() const
     * \brief Accesseur en lecture de l'attribut numReel
     */
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




#endif // NUMERIQUE

