#include "computer.h"
#include <algorithm>

void decompCommande(const QString& c,int &i, int &j);
QString Programme::toExpr()const
{
    QString s;
    QString exp="";
    int i=0, j=0;
    QString p=prog;
    while(i < (prog.length()))
    {
        decompCommande(prog, i, j);

        if(i-j != 0)
        {
            s = p.mid(j,i-j);
            if (s[0]=='[')
            {
                Programme temp(s);
                s=temp.toExpr();
            }
            else if (s[0]==']')
            {
                return exp;
            }
            else
            {

            if (estUnOperateur(s))
                exp=exp+" "+s;
            else
                exp=exp+" '"+s+"'";
            }
        }
        else
        {
            s = p.mid(j,1);
            if (estUnOperateur(s))
                exp=exp+" "+s;
            else
                exp=exp+" '"+s+"'";
        }

        i++;
        j = i;

    }
    return exp;
}


bool estUnIndentificateur(const Expression& e)
{
    int i=0;
    QString s=e.getExp();
    if (s[i] >= 'A' && s[i] <= 'Z')
    {
         while (i<(e.getExp().length()))
         {
             if((s[i] < 'A' && s[i] > 'Z') || (s[i] < '0' && s[i] > '9'))
                 return false;
             i++;
         }
         return true;
    }
    return false;

}



Litterale& Atome::getLitterale() const
{
        if (exp==nullptr) throw ComputerException("Atome : tentative d'acces a une Litterale inexistante");
        return *exp;
}

Atome Expression::operatorSTO(Litterale& l)
{
    if (l.getType()=="Numerique")
    {
        Numerique n=dynamic_cast<Numerique&>(l);
        return Atome(exp,new Numerique(n));
    }
    if (l.getType()=="Expression")
    {
        Expression n=dynamic_cast<Expression&>(l);
        return Atome(exp,new Expression(n));
    }
    if (l.getType()=="Programme")
    {
        Programme n=dynamic_cast<Programme&>(l);
        return Atome(exp,new Programme(n));
    }
    return NULL;
}

Expression Expression::operator<=(const Expression& e)
{
    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' )
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '+' || e.exp[i] == '-' || e.exp[i] == '*' || e.exp[i] == '/')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+"<="+e.exp;
    else
        res= "("+exp+")<=("+e.exp+")";
    return Expression(res);
}

Expression Expression::operator>=(const Expression& e)
{
    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' )
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '+' || e.exp[i] == '-' || e.exp[i] == '*' || e.exp[i] == '/')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+">="+e.exp;
    else
        res= "("+exp+")>=("+e.exp+")";
    return Expression(res);
}

Expression Expression::operator<(const Expression& e)
{
    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' )
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '+' || e.exp[i] == '-' || e.exp[i] == '*' || e.exp[i] == '/')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+"<"+e.exp;
    else
        res= "("+exp+")<("+e.exp+")";
    return Expression(res);
}

Expression Expression::operator>(const Expression& e)
{
    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' )
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '+' || e.exp[i] == '-' || e.exp[i] == '*' || e.exp[i] == '/')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+">"+e.exp;
    else
        res= "("+exp+")>("+e.exp+")";
    return Expression(res);
}

Expression Expression::operator!=(const Expression& e)
{

    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '<' || exp[i] == '>' || exp[i] == '<=' || exp[i] == '>=')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '+' || e.exp[i] == '-' || e.exp[i] == '*' || e.exp[i] == '/' || e.exp[i] == '<' || e.exp[i] == '>' || e.exp[i] == '<=' || e.exp[i] == '>=')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+"!="+e.exp;
    else
        res= "("+exp+")!=("+e.exp+")";
    return Expression(res);
}


Expression Expression::operator==(const Expression& e)
{

    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '<' || exp[i] == '>' || exp[i] == '<=' || exp[i] == '>=')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '+' || e.exp[i] == '-' || e.exp[i] == '*' || e.exp[i] == '/' || e.exp[i] == '<' || e.exp[i] == '>' || e.exp[i] == '<=' || e.exp[i] == '>=')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+"=="+e.exp;
    else
        res= "("+exp+")==("+e.exp+")";
    return Expression(res);
}

Expression Expression::operatorAND(const Expression& e)
{
    QString res;
    res="AND("+exp+","+e.exp+")";

    return Expression(res);
}

Expression Expression::operatorOR(const Expression& e)
{
    QString res;
    res="OR("+exp+","+e.exp+")";

    return Expression(res);
}

Expression Expression::operatorNOT()
{
    QString res;
    res="NOT("+exp+")";

    return Expression(res);
}


Expression Expression::operatorNEG()
{
    QString res;
    res="NEG("+exp+")";

    return Expression(res);
}

Expression Expression::operator*(const Expression& e)
{
   /* QString res;
    res=exp+"*"+e.exp;

    return Expression(res);*/

    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '+' || exp[i] == '-')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '-' || e.exp[i] == '+')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+"*"+e.exp;
    else
        res= "("+exp+")*("+e.exp+")";
    return Expression(res);
}

Expression Expression::operator/(const Expression& e)
{
    /*QString res;
    res=exp+"/"+e.exp;

    return Expression(res);*/
    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '+' || exp[i] == '-')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '-' || e.exp[i] == '+')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+"/"+e.exp;
    else
        res= "("+exp+")/("+e.exp+")";
    return Expression(res);

}

Expression Expression::operator$(const Expression& e)
{
    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '+' || e.exp[i] == '-' || e.exp[i] == '*' || e.exp[i] == '/')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+"$"+e.exp;
    else
        res= "("+exp+")$("+e.exp+")";
    return Expression(res);
}

Expression Expression::operator+(const Expression& e)
{
    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '/' || exp[i] == '*' ||  exp[i] == '$')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '/' || e.exp[i] == '*' ||  exp[i] == '$')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+"+"+e.exp;
    else
        res= "("+exp+")+("+e.exp+")";
    return Expression(res);
}

Expression Expression::operator-(const Expression& e)
{
    int i=0;
    bool priorite=true;
    while(i < (exp.length()))
    {
        if(exp[i]== '(')
        {
            while(i < (exp.length()) && exp[i]!= ')')
                i++;
        }
        else
        {
            if (exp[i] == '/' || exp[i] == '*' ||  exp[i] == '$')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }

    while(i < (e.exp.length()))
    {
        if(e.exp[i]== '(')
        {
            while(i < (e.exp.length()) && e.exp[i]!= ')')
                i++;
        }
        else
        {
            if (e.exp[i] == '/' || e.exp[i] == '*' ||  exp[i] == '$')
            {
                priorite=false;
                break;
            }
            i++;
        }
    }
    QString res;
    if (priorite)
       res=exp+"-"+e.exp;
    else
        res= "("+exp+")-("+e.exp+")";
    return Expression(res);
}

//Pour enlever les espaces dans les expressions entrées par l'utilisateur
QString RemoveSpaces(QString s)
{
    QString res = "";
    for(int i = 0; i < s.length(); i++)
    {
        if(s[i] != ' ')
            res.append(s[i]);
    }
    return res;
}

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

Numerique Numerique::operator$(const Numerique& n)
{
    Numerique res(numReel,n.numReel,typeRe,n.typeRe, denomReel, n.denomReel);
    return res;
}


Numerique Numerique::operatorDIV(const Numerique& n)
{
   int num=(int)numReel/(int)n.numReel;
   Numerique res(num,0,"entier","null",1, 1);
   return res;

}

Numerique Numerique::operatorMOD(const Numerique& n)
{
   int num=(int)numReel%(int)n.numReel;
   Numerique res(num,0,"entier","null",1, 1);
   return res;
}

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

Numerique Numerique::operatorNEG()
{
    Numerique res(-numReel,-numIm,typeRe,typeIm,denomReel, denomIm);
    return res;
}

Numerique Numerique::operatorNUM()
{
    Numerique res(numReel,"entier");
    return res;
}

Numerique Numerique::operatorDEN()
{

    Numerique res(denomReel,"entier");
    return res;
}

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

void Numerique::simplificationRe()
{
    // si le numerateur est 0, le denominateur prend la valeur 1
    if (numReel==0) { denomReel=1; return; }
    /* un denominateur ne devrait pas Ãªtre 0;
    si c'est le cas, on sort de la mÃ©thode */
    if (denomReel==0) return;
    /* utilisation de l'algorithme d'Euclide pour trouver le Plus Grand Commun
    Denominateur (PGCD) entre le numerateur et le denominateur */
    int a=numReel, b=denomReel;
    // on ne travaille quâ€™avec des valeurs positives...
    if (a<0) a=-a; if (b<0) b=-b;
    while(a!=b){ if (a>b) a=a-b; else b=b-a; }
    // on divise le numerateur et le denominateur par le PGCD=a
    numReel/=a; denomReel/=a;
    // si le denominateur est negatif, on fait passer le signe - au numÃ©rateur
    if (denomReel<0) { denomReel=-denomReel; numReel=-numReel; }
}

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

LitteraleManager::Handler LitteraleManager::handler=LitteraleManager::Handler();



void LitteraleManager::libererInstance()
{
    delete handler.instance;
    handler.instance=nullptr;
}


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

void LitteraleManager::agrandissementCapacite()
{
    Litterale** newtab=new Litterale*[(nbMax+1)*2];
    for(unsigned int i=0; i<nb; i++) newtab[i]=exps[i];
    Litterale**  old=exps;
    exps=newtab;
    nbMax=(nbMax+1)*2;
    delete old;
}



Litterale& LitteraleManager::addLitteraleE(QString v)
{
    if (nb==nbMax) agrandissementCapacite();
    exps[nb++]=new Expression(v);
    return *exps[nb-1];
}

Litterale& LitteraleManager::addLitteraleA(QString v)
{
    if (nb==nbMax) agrandissementCapacite();
    exps[nb++]=new Atome(v);
    return *exps[nb-1];
}

Litterale& LitteraleManager::addLitteraleP(QString v)
{
    if (nb==nbMax) agrandissementCapacite();
    exps[nb++]=new Programme(v);
    return *exps[nb-1];
}

Litterale& LitteraleManager::addLitterale(int v)
{
    if (nb==nbMax) agrandissementCapacite();
    exps[nb++]=new Numerique(v);
    return *exps[nb-1];
}

Litterale& LitteraleManager::addLitterale(double v)
{
    if (nb==nbMax) agrandissementCapacite();
    exps[nb++]=new Numerique(v);
    return *exps[nb-1];
}


void LitteraleManager::removeLitterale(Litterale& e)
{
    unsigned int i=0;
    while(i<nb && exps[i]!=&e) i++;
    if (i==nb) throw ComputerException("elimination d'une Litterale inexistante");
    delete exps[i];
    i++;
    while(i<nb) { exps[i-1]=exps[i]; i++; }
    nb--;
}



LitteraleManager::~LitteraleManager()
{
    for(unsigned int i=0; i<nb; i++) delete exps[i];
    delete[] exps;
}

Litterale& Item::getLitterale() const
{
        if (exp==nullptr) throw ComputerException("Item : tentative d'acces a une Litterale inexistante");
        return *exp;
}


void Pile::agrandissementCapacite()
{
    Item* newtab=new Item[(nbMax+1)*2];
    for(unsigned int i=0; i<nb; i++) newtab[i]=items[i];
    Item*  old=items;
    items=newtab;
    nbMax=(nbMax+1)*2;
    delete[] old;
}

void Pile::push(Litterale& e)
{
    if (nb==nbMax) agrandissementCapacite();
    items[nb].setLitterale(e);
    nb++;
    modificationEtat();
}


void Pile::pop()
{
    nb--;
    items[nb].raz();
    modificationEtat();
}

void Pile::affiche(QTextStream& f) const
{
    f<<"********************************************* \n";
    f<<"M : "<<message<<"\n";
    f<<"---------------------------------------------\n";
    for(unsigned int i=nbAffiche; i>0; i--) {
        if (i<=nb) f<<i<<": "<<items[nb-i].getLitterale().toString()<<"\n";
        else f<<i<<": \n";
    }
    f<<"---------------------------------------------\n";
}


Pile::~Pile()
{
    delete[] items;
}

Litterale& Pile::top() const
{
    if (nb==0) throw ComputerException("aucune Litterale sur la pile");
    return items[nb-1].getLitterale();
}

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

void Controleur::agrandissementCapacite()
{
    Atome** newtab=new Atome*[(nbAtomesMax+1)*2];
    for(unsigned int i=0; i<nbAtomes; i++) newtab[i]=atomes[i];
    Atome**  old=atomes;
    atomes=newtab;
    nbAtomesMax=(nbAtomesMax+1)*2;
    delete[] old;
}

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

bool estUneExpression(const QString s)
{
    if( s[0]=='\'' && s[s.length()-1]=='\'' )
        return true;
    return false;
}

bool estUnProgramme(QString s)
{
    if( s[0]=='[' && s[s.length()-1]==']' )
        return true;
    return false;
}

bool estUnOperateurBinaire(const QString s)
{
    if (s=="+") return true;
    if (s=="-") return true;
    if (s=="*") return true;
    if (s=="/") return true;
    if (s=="$") return true;
    if (s=="DIV") return true;
    if (s=="MOD") return true;
    if (s=="AND") return true;
    if (s=="OR") return true;
    if (s=="SWAP") return true;
    if (s=="==") return true;
    if (s=="!=") return true;
    if (s==">=") return true;
    if (s=="<=") return true;
    if (s==">") return true;
    if (s=="<") return true;
    if (s=="STO") return true;
    return false;
}

bool estUnOperateurUnaire(const QString s)
{
    if (s=="NEG") return true;
    if (s=="NUM") return true;
    if (s=="DEN") return true;
    if (s=="RE") return true;
    if (s=="IM") return true;
    if (s=="DUP") return true;
    if (s=="DROP") return true;
    if (s=="NOT") return true;
    if (s=="FORGET") return true;
    if (s=="EVAL") return true;
    if (s=="EDIT") return true;
    return false;
}

bool estUnOperateurSansArg(const QString s)
{
    if (s=="CLEAR") return true;
    if (s=="UNDO") return true;
    if (s=="REDO") return true;
    if (s=="LASTARGS") return true;
    return false;
}

bool estUnOperateur(const QString s)
{
    return(estUnOperateurBinaire(s) || estUnOperateurSansArg(s) || estUnOperateurUnaire(s));
}

bool estUnEntier(const QString s)
{
   bool ok=false;
   s.toInt(&ok);
   return ok;
}

bool estUnReel(const QString s)
{
   bool ok=false;
   s.toDouble(&ok);
   return ok;
}

bool estUnRationnel(const QString c, QString s, int i)
{
    if(estUnEntier(s) && c[i]=='/')
    {
        i++;
        int j = i;
        while(i < (c.length()-1) && !estUnOperateurBinaire(c[i]) && c[i]!=' ')
        {
            i++;
        }
        if(i == c.length()-1)
        {
            i++;
        }
        s = c.mid(j,i-j);
        if(estUnEntier(s))
            return true;
        else return false;
    }
    return false;
}

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

Numerique Controleur::managePileOpeNumAndNum(Numerique v1, Numerique v2,QString s, Numerique res)
{
    if (s == "SWAP")
    {
        res=v1;
        Litterale& l=expMng.addLitterale(v2);
        expAff.push(l);
    }
    return res;
}

Expression Controleur::manageNumOpeNumAndExpr(Expression v1, Expression v2E, QString s, Expression res)
{
    if (s == "+") res = v1 + v2E;
    if (s == "-") res = v1 - v2E;
    if (s == "*") res = v1 * v2E;
    if (s == "/") res = v1 / v2E;
    if (s == "$") res = v1.operator$(v2E);
    return res;
}

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

Expression Controleur::managePileOpeNumAndExpr(Expression v1, Numerique v2,QString s, Expression res)
{
    if (s == "SWAP")
    {
        res=v1;
        Litterale& l=expMng.addLitterale(v2);
        expAff.push(l);
    }
    return res;
}

Expression Controleur::manageNumOpeExprAndExpr(Expression v1, Expression v2, QString s, Expression res)
{
    if (s == "+") res = v1 + v2;
    if (s == "-") res = v1 - v2;
    if (s == "*") res = v1 * v2;
    if (s == "/") res = v1 / v2;
    if (s == "$") res = v1.operator$(v2);
    return res;
}

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

Expression Controleur::managePileOpeExprAndExpr(Expression v1, Expression v2,QString s, Expression res)
{
    if (s == "SWAP")
    {
        res=v1;
        Litterale& l=expMng.addLitterale(v2);

        expAff.push(l);

    }
    return res;
}

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

Numerique Controleur::managePileOpeExprAndNum(Numerique v1, Expression v2,QString s, Numerique res)
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
}

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

void decompCommande(const QString& c,int &i, int &j)
{
    while(i < (c.length()-1) && c[i] == ' ')
    {
        i++;
    }
    j = i;
    if(i < (c.length()-1) && c[i] == '-')
        i++;
    if (i < (c.length()-1) && c[i] != '\'' && c[i] != '[')
    {
        if((c[i] == '<' || c[i] == '>') && c[i+1] == '=')
            i+= 2;
        while(i < (c.length()-1) && !estUnOperateurBinaire(c[i]) && c[i]!=' ')
        {
            i++;
        }
        if(i == c.length()-1)
        {
            i++;
        }
        else if(i < (c.length()-1) && estUnOperateurBinaire(c[i]) && i == j)
        {
            i++;
        }

    }
    else if (i < (c.length()-1) && c[i] == '\'')
    {
        i++;
        while(i < (c.length()-1) && c[i]!='\'')
        {
            i++;
        }

        i++;

        if(i < c.length()-1 && estUnOperateurBinaire(c[i]) && i == j)
        {
            i++;
        }
    }
    else if (i < (c.length()-1) && c[i] == '[')
    {
        i++;
        int cpt=1;// compteur de [
        while(i < (c.length()-1) /*&& c[i]!=']'*/ && cpt!=0)
        {
            i++;
            if (c[i] == '[')
                cpt++;
            if (c[i] == ']')
                cpt--;

        }

        i++;

        if(i < c.length()-1 && estUnOperateurBinaire(c[i]) && i == j)
        {
            i++;
        }
    }
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

void Controleur::manageBinOpe(bool beep, QString s, int &i, int &j)
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

                res = managePileOpeNumAndNum(v1, v2, s, res);

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

                res = managePileOpeNumAndExpr(v1, v2,s, res);

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
                    managePileOpeT2AndT1(v1, v2,s, res);
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
                            && estUnIndentificateur(v2))
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

                res = managePileOpeExprAndExpr(v1, v2, s, res);

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
                            !estUnOperateurSansArg(v2.getExp()) && estUnIndentificateur(v2))
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
                    res = managePileOpeExprAndNum(v1, v2, s, res);
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
                    if(!estUnOperateurBinaire(v2.getExp()) && !estUnOperateurUnaire(v2.getExp()) && !estUnOperateurSansArg(v2.getExp()) && estUnIndentificateur(v2))
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
                    managePileOpeT2AndT1(v1, v2,s, res);
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
                        managePileOpeT2AndT1(v1, v2,s, res);
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
                        managePileOpeT2AndT1(v1, v2,s, res);
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

void Controleur::manageUnOpe(bool beep, QString s, int &i, int &j)
{    
    /*if(expAff.top().getType()=="Atome")
    {
        try
        {

            Atome v1=dynamic_cast<Atome&>(expAff.top());
            expMng.removeLitterale(expAff.top());
            expAff.pop();


            Atome res("");// on initialise res a zero
            if (s == "FORGET")
            {
                res = v1.operatorFORGET();
                removeAtome(v1);
                Litterale& e=expMng.addLitterale(res);
                expAff.push(e);
            }
            else
            {
                if (v1.getLitterale().getType()=="Numerique")
                {
                    Numerique n=dynamic_cast<Numerique&>(v1.getLitterale());
                    expAff.push(expMng.addLitterale(n));
                }
                if (v1.getLitterale().getType()=="Programme")
                {
                    Programme p=dynamic_cast<Programme&>(v1.getLitterale());
                    expAff.push(expMng.addLitterale(p));

                }
                if (v1.getLitterale().getType()=="Expression")
                {
                    Expression p=dynamic_cast<Expression&>(v1.getLitterale());
                    expAff.push(expMng.addLitterale(p));

                }
            }



        }
        catch(std::bad_cast& e)
        {
            if(beep)
                Beep(500,500);
            expAff.setMessage(e.what());
        }
    }*/


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
                if(estUnIndentificateur(v1.getExp()) && !estUnOperateur(v1.getExp()))
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


            if (s == "NOT") res = v1.operatorNOT();
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

                        if(str != "UNDO")
                        {

                        }

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
                                manageBinOpe(false, str, i, j); // Gère toutes les opérations à effectuer avec l'opérateur binaire reçu
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
                                manageUnOpe(false, str, i, j); // Gère toutes les opérations à effectuer avec l'opérateur unaire reçu
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
                        //i++;
                        //j = i;
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
    if(redo)
        delete redo;
    redo = new Memento(expMng, expAff, lastOpe);
    reinstateMemento(undo);
}


void Controleur::redoCommand()
{
    reinstateMemento(redo);
}


void Controleur::updateUndo()
{
    if(undo)
        delete undo;
    undo = new Memento(expMng, expAff, lastOpe);
}

void Controleur::updateRedo()
{
    if(redo)
        delete redo;
    redo = new Memento(expMng, expAff, lastOpe);
}

void Controleur::updateLastArgs()
{
    if(lastArgs)
        delete lastArgs;
    lastArgs = new Memento(expMng, expAff, lastOpe);
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
        else if(estUnIndentificateur(s) && !estUnOperateur(s))
        {
            if (chercherAtome(s)== -1)// n'existe pas
            {
                Expression e(s);
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
                if (a.getLitterale().getType()=="Programme")
                {
                    Programme p=dynamic_cast<Programme&>(a.getLitterale());
                    expAff.push(expMng.addLitterale(p));

                }
            }

        }
        else if(estUnOperateurBinaire(s))
        {
            if (expAff.taille() >= 2)
            {
                manageBinOpe(beepOption, s, i, j); // Gère toutes les opérations à effectuer avec l'opérateur binaire reçu
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
                manageUnOpe(beepOption, s, i, j); // Gère toutes les opérations à effectuer avec l'opérateur unaire reçu
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


}
