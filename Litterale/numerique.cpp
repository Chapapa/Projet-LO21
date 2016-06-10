#include "numerique.h"

/**
 * \fn Numerique Numerique::operator+(const Numerique& n)
 * \brief Operateur +
 */
Numerique Numerique::operator+(const Numerique& n)
{
    double nr;
    int dr;
    double ni;
    int di;
    if(typeRe == "reel" || n.typeRe == "reel")
    {
        nr = (numReel/denomReel)+(n.numReel/n.denomReel);
        dr = 1;
    }
    else
    {
        nr=numReel*n.denomReel + n.numReel*denomReel;
        dr=denomReel*n.denomReel;
    }
    if(typeIm == "reel" || n.typeIm == "reel")
    {
        ni = (numIm/denomIm)+(n.numIm/n.denomIm);
        di = 1;
    }
    else
    {
        ni=numIm*n.denomIm+n.numIm*denomIm;
        di=denomIm*n.denomIm;
    }

    QString tRe=getResTypeRe(nr,dr);
    QString tIm=getResTypeIm(ni,di);

    Numerique res(nr,ni,tRe,tIm,dr,di);

    return res;
}

/**
 * \fn Numerique Numerique::operator-(const Numerique& n)
 * \brief Operateur -
 */
Numerique Numerique::operator-(const Numerique& n)
{
    double nr;
    int dr;
    double ni;
    int di;
    if(typeRe == "reel" || n.typeRe == "reel")
    {
        nr = (numReel/denomReel)-(n.numReel/n.denomReel);
        dr = 1;
    }
    else
    {
        nr=numReel*n.denomReel-n.numReel*denomReel;
        dr=denomReel*n.denomReel;
    }
    if(typeIm == "reel" || n.typeIm == "reel")
    {
        ni = (numIm/denomIm)-(n.numIm/n.denomIm);
        di = 1;
    }
    else
    {
        ni=numIm*n.denomIm-n.numIm*denomIm;
        di=denomIm*n.denomIm;
    }
    QString tRe=getResTypeRe(nr,dr);
    QString tIm=getResTypeIm(ni,di);

    Numerique res(nr,ni,tRe,tIm,dr,di);

    return res;
}

/**
 * \fn Numerique Numerique::operator*(const Numerique& n)
 * \brief Operateur *
 */
Numerique Numerique::operator*(const Numerique& n)
{
    double nr;
    int dr;
    double ni;
    int di;
    if(typeRe == "reel" || n.typeRe == "reel")
    {
        nr = (numReel/denomReel)*(n.numReel/n.denomReel);
        dr = 1;
    }
    else
    {
        nr=(numReel*n.numReel);
        dr=denomReel*n.denomReel;
    }
    if(typeIm == "reel" || n.typeIm == "reel")
    {
        ni = (numIm/denomIm)*(n.numIm/n.denomIm);
        di = 1;
    }
    else
    {
        ni=(numIm*n.numIm);
        di=denomIm*n.denomIm;
    }

    QString tRe=getResTypeRe(nr,dr);
    QString tIm=getResTypeIm(ni,di);

    Numerique res(nr,ni,tRe,tIm,dr,di);

    return res;
}

/**
 * \fn Numerique Numerique::operator/(const Numerique& n)
 * \brief Operateur /
 */
Numerique Numerique::operator/(const Numerique& n)
{
    double nr;
    int dr;
    double ni;
    int di;
    if(typeRe == "reel" || n.typeRe == "reel")
    {
        nr = (numReel/denomReel)/(n.numReel/n.denomReel);
        dr = 1;
    }
    else
    {
        nr=numReel*n.denomReel;
        dr=denomReel*n.numReel;
    }
    if(typeIm == "reel" || n.typeIm == "reel")
    {
        ni = (numIm/denomIm)/(n.numIm/n.denomIm);
        di = 1;
    }
    else
    {
        ni=numIm*n.denomIm;
        di=denomIm*n.numIm;
    }

    QString tRe;
    QString tIm;
    simplificationRe();
    simplificationIm();
    tRe = getResTypeRe(nr, dr);
    tIm = getResTypeIm(ni, di);

    Numerique res(nr,ni,tRe,tIm,dr,di);

    return res;

}

/**
 * \fn Numerique Numerique::operator$(const Numerique& n)
 * \brief Operateur $
 */
Numerique Numerique::operator$(const Numerique& n)
{
    Numerique res(numReel,n.numReel,typeRe,n.typeRe, denomReel, n.denomReel);
    return res;
}

/**
 * \fn Numerique Numerique::operatorDIV(const Numerique& n)
 * \brief Operateur DIV
 */
Numerique Numerique::operatorDIV(const Numerique& n)
{
   int num=(int)numReel/(int)n.numReel;
   Numerique res(num,0,"entier","null",1, 1);
   return res;

}

/**
 * \fn Numerique Numerique::operatorMOD(const Numerique& n)
 * \brief Operateur MOD
 */
Numerique Numerique::operatorMOD(const Numerique& n)
{
   int num=(int)numReel%(int)n.numReel;
   Numerique res(num,0,"entier","null",1, 1);
   return res;
}

/**
 * \fn Numerique Numerique::operator==(const Numerique& n)
 * \brief Operateur ==
 */
Numerique Numerique::operator==(const Numerique& n)
{

    if (numReel==n.numReel && denomReel==n.denomReel && numIm==n.numIm && denomIm==n.denomIm)
    {
        Numerique res1(1,"entier");
        return res1;
    }
    else
    {
        Numerique res0(0,"entier");
        return res0;
    }

}

/**
 * \fn Numerique Numerique::operator!=(const Numerique& n)
 * \brief Operateur !=
 */
Numerique Numerique::operator!=(const Numerique& n)
{

    if (numReel!=n.numReel || denomReel!=n.denomReel || numIm!=n.numIm || denomIm!=n.denomIm)
    {
        Numerique res1(1,"entier");
        return res1;
    }
    else
    {
        Numerique res0(0,"entier");
        return res0;
    }

}

/**
 * \fn Numerique Numerique::operator>=(const Numerique& n)
 * \brief Operateur >=
 */
Numerique Numerique::operator>=(const Numerique& n)
{
    double temp1=(double)numReel/(double)denomReel;
    double temp2=(double)n.numReel/(double)n.denomReel;
    if (temp1 >= temp2)
    {
        Numerique res1(1,"entier");
        return res1;
    }
    else
    {
        Numerique res0(0,"entier");
        return res0;
    }
}

/**
 * \fn Numerique Numerique::operator<=(const Numerique& n)
 * \brief Operateur <=
 */
Numerique Numerique::operator<=(const Numerique& n)
{
    double temp1=(double)numReel/(double)denomReel;
    double temp2=(double)n.numReel/(double)n.denomReel;
    if (temp1 <= temp2)
    {
        Numerique res1(1,"entier");
        return res1;
    }
    else
    {
        Numerique res0(0,"entier");
        return res0;
    }
}


/**
 * \fn Numerique Numerique::operator<(const Numerique& n)
 * \brief Operateur <
 */
Numerique Numerique::operator<(const Numerique& n)
{
    double temp1=(double)numReel/(double)denomReel;
    double temp2=(double)n.numReel/(double)n.denomReel;
    if (temp1 < temp2)
    {
        Numerique res1(1,"entier");
        return res1;
    }
    else
    {
        Numerique res0(0,"entier");
        return res0;
    }
}

/**
 * \fn Numerique Numerique::operator>(const Numerique& n)
 * \brief Operateur >
 */
Numerique Numerique::operator>(const Numerique& n)
{
    double temp1=(double)numReel/(double)denomReel;
    double temp2=(double)n.numReel/(double)n.denomReel;
    if (temp1 > temp2)
    {
        Numerique res1(1,"entier");
        return res1;
    }
    else
    {
        Numerique res0(0,"entier");
        return res0;
    }
}

/**
 * \fn Numerique Numerique::operatorAND(const Numerique& n)
 * \brief Operateur AND
 */
Numerique Numerique::operatorAND(const Numerique& n)
{

    if ( numReel>0 && n.numReel>0)
    {
        Numerique res1(1,"entier");
        return res1;
    }
    else if (typeIm!="null" && n.typeIm!="null" && numIm>0 && n.numIm>0 )
    {
        Numerique res1cmplx(1,"entier");
        return res1cmplx;
    }
    else if (numReel>0  && n.typeIm!="null" && n.numIm>0 )
    {
        Numerique res1cmplx(1,"entier");
        return res1cmplx;
    }
    else if (n.numReel>0  && typeIm!="null" && numIm>0 )
    {
        Numerique res1cmplx(1,"entier");
        return res1cmplx;
    }
    else
    {
        Numerique res0(0,"entier");
        return res0;
    }
}

/**
 * \fn Numerique Numerique::operatorOR(const Numerique& n)
 * \brief Operateur OR
 */
Numerique Numerique::operatorOR(const Numerique& n)
{
    if ( numReel>0 || n.numReel>0)
    {
        Numerique res1(1,"entier");
        return res1;
    }
    else if ((typeIm!="null" &&  numIm>0) || (n.typeIm!="null" && n.numIm>0))
    {
        Numerique res1cmplx(1,"entier");
        return res1cmplx;
    }
    else
    {
        Numerique res0(0,"entier");
        return res0;
    }

}

/**
 * \fn Numerique Numerique::operatorNOT()
 * \brief Operateur NOT
 */
Numerique Numerique::operatorNOT()
{
    if ( numReel>0)
    {
        Numerique res0(0,"entier");
        return res0;
    }
    if ( numIm>0)
    {
        Numerique res0cmplx(0,"entier");
        return res0cmplx;
    }
    else
    {
        Numerique res1(1,"entier");
        return res1;
    }
}

/**
 * \fn Numerique Numerique::operatorNEG()
 * \brief Operateur NEG
 */
Numerique Numerique::operatorNEG()
{
    Numerique res(-numReel,-numIm,typeRe,typeIm,denomReel, denomIm);
    return res;
}

/**
 * \fn Numerique Numerique::operatorNUM()
 * \brief Operateur NUM : retourne le numerateur
 */
Numerique Numerique::operatorNUM()
{
    Numerique res(numReel,"entier");
    return res;
}

/**
 * \fn Numerique Numerique::operatorDEN()
 * \brief Operateur DEN : retourne le denominateur
 */
Numerique Numerique::operatorDEN()
{

    Numerique res(denomReel,"entier");
    return res;
}

/**
 * \fn Numerique Numerique::operatorRE()
 * \brief Operateur RE : retourne la partie reelle
 */
Numerique Numerique::operatorRE()
{
    QString typeRes;
    if(denomReel==1)//pas un rationnel
    {
        if (typeRe=="entier")
        {
             typeRes="entier";
        }
        if (typeRe=="reel")
        {
             typeRes="reel";
        }
    }
    else//rationnel
    {
        typeRes="rationnel";
    }

    Numerique res(numReel,denomReel,typeRes);
    return res;
}

/**
 * \fn Numerique Numerique::operatorIM()
 * \brief Operateur IM : retourne la partie imaginaire
 */
Numerique Numerique::operatorIM()
{
    QString typeRes;
    if(denomIm==1)//pas un rationnel
    {
        if (typeIm=="entier")
        {
             typeRes="entier";
        }
        if (typeIm=="reel")
        {
             typeRes="reel";
        }
    }
    else//rationnel
    {
        typeRes="rationnel";
    }

    Numerique res(numIm,denomIm,typeRes);
    return res;
}

/**
 * \fn QString Numerique::getResTypeRe( double nr, int dr)
 * \brief La methode permet de determiner le type de Numerique de la partie reelle resultant de l'operation
 *
 * \param nr Numerateur reel
 * \param dr Denominateur reel
 * \return La fonction retourne "entier", "reel", "rationnel"
 */
QString Numerique::getResTypeRe( double nr, int dr)
{
    QString res;
    if(dr == 1)
    {
        if(floor(nr) == nr)
        {
            res = "entier";
        }
        else
        {
            res = "reel";
        }
    }
    else
    {
        res="rationnel";
    }
    return res;

}

/**
 * \fn QString Numerique::getResTypeIm(double ni, int di)
 * \brief La methode permet de determiner le type de Numerique de la partie imaginaire resultant de l'operation
 *
 * \param ni Numerateur imaginaire
 * \param di Denominateur imaginaire
 * \return La fonction retourne "entier", "reel", "rationnel"
 */
QString Numerique::getResTypeIm(double ni, int di)
{
    QString res;
    if(ni==0) return "null";
    if(di==1)//pas un rationnel
    {
        if(floor(ni) == ni)
        {
            res = "entier";
        }
        else
        {
            res = "reel";
        }
    }
    else
    {
        res="rationnel";
    }
    return res;
}

/**
 * \fn void Numerique::simplificationRe()
 * \brief Simplification de la partie reel d un numerique si il s'agit d'un rationnel
 */
void Numerique::simplificationRe()
{
    // si le numerateur est 0, le denominateur prend la valeur 1
    if (numReel==0) { denomReel=1; return; }
    /* un denominateur ne devrait pas etre 0;
    si c'est le cas, on sort de la methode */
    if (denomReel==0) return;
    /* utilisation de l'algorithme d'Euclide pour trouver le Plus Grand Commun
    Denominateur (PGCD) entre le numerateur et le denominateur */
    int a=numReel, b=denomReel;
    // on ne travaille qu avec des valeurs positives...
    if (a<0) a=-a; if (b<0) b=-b;
    while(a!=b){ if (a>b) a=a-b; else b=b-a; }
    // on divise le numerateur et le denominateur par le PGCD=a
    numReel/=a; denomReel/=a;
    // si le denominateur est negatif, on fait passer le signe - au numerateur
    if (denomReel<0) { denomReel=-denomReel; numReel=-numReel; }
}

/**
 * \fn void Numerique::simplificationIm()
 * \brief Simplification de la partie imaginaire d un numerique si il s'agit d'un rationnel
 */
void Numerique::simplificationIm()
{
    // si le numerateur est 0, le denominateur prend la valeur 1
    if (numIm==0) { denomIm=1; return; }
    /* un denominateur ne devrait pas Ãªtre 0;
    si câ€™est le cas, on sort de la mÃ©thode */
    if (denomIm==0) return;
    /* utilisation de lâ€™algorithme dâ€™Euclide pour trouver le Plus Grand Commun
    Denominateur (PGCD) entre le numerateur et le denominateur */
    int a=numIm, b=denomIm;
    // on ne travaille quâ€™avec des valeurs positives...
    if (a<0) a=-a; if (b<0) b=-b;
    while(a!=b){ if (a>b) a=a-b; else b=b-a; }
    // on divise le numerateur et le denominateur par le PGCD=a
    numIm/=a; denomIm/=a;
    // si le denominateur est nÃ©gatif, on fait passer le signe - au numÃ©rateur
    if (denomIm<0) { denomIm=-denomIm; numIm=-numIm; }
}

/**
 * \fn void Numerique::setRationnelRe(int n,int d)
 * \brief Accesseur en ecriture pour la partie reelle de type rationnel d'un numerique
 */
void Numerique::setRationnelRe(int n,int d)
{
    if(d==0)
    {
        throw ComputerException("fraction exception division par 0");
    }
    else
    {
        numReel=n;
        denomReel=d;
    }
    simplificationRe();
    if (denomReel==1)
        setTypeRe("entier");

}
/**
 * \fn void Numerique::setRationnelIm(int n,int d)
 * \brief Accesseur en ecriture pour la partie imaginaire de type rationnel d'un numerique
 */
void Numerique::setRationnelIm(int n,int d)
{
    if(d==0)
    {
        throw ComputerException("fraction exception division par 0");
    }

    else
    {
        numIm=n;
        denomIm=d;
    }
    simplificationIm();
    if (denomIm==1)
        setTypeIm("entier");
}

/**
 * \fn QString Numerique::toString() const
 * \brief Transformation d'un numerique en chaine de caractere pour son affichage
 */
QString Numerique::toString() const
{
    QString val;
    QString sNumR = QString::number(numReel);
    QString sDenomR = QString::number(denomReel);
    QString sNumI = QString::number(numIm);
    QString sDenomI = QString::number(denomIm);

    if(getTypeIm()=="null" &&(getTypeRe()=="entier" || getTypeRe()=="reel"))
    {
        val = sNumR;
        return val;
    }
    else if(getTypeIm()=="null" && getTypeRe()=="rationnel")
    {
        val += sNumR;
        if(denomReel != 1)
        {
            val += "/" + sDenomR;
        }
        return val;
    }
    else if(getTypeIm()!="null")
    {
        if(numReel != 0)
        {
            val += QString::number(numReel);
            if(denomReel != 1)
            {
                val += "/" + sDenomR;
            }
        }
        if(numIm != 0)
        {
            val += "$" + sNumI;
            if(denomIm != 1)
            {
                val += "/" + sDenomI;
            }
        }
        return val;
    }
    else
    {
        return NULL;
    }
}


