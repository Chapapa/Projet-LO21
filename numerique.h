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




#endif // NUMERIQUE

