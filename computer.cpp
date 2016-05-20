#include "computer.h"
#include <algorithm>


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

Expression Expression::operatorNOT(const Expression& e)
{
    QString res;
    res="NOT("+exp+","+e.exp+")";

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
    QString res;
    res=exp+"*"+e.exp;

    return Expression(res);
}

Expression Expression::operator/(const Expression& e)
{
    QString res;
    res=exp+"/"+e.exp;

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
            if (exp[i] == '/' || exp[i] == '*')
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
            if (e.exp[i] == '/' || e.exp[i] == '*')
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
            if (exp[i] == '/' || exp[i] == '*')
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
            if (e.exp[i] == '/' || e.exp[i] == '*')
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


Numerique Numerique::operator+(const Numerique& n)
{
    double nr=numReel*n.denomReel + n.numReel*denomReel;
    int dr=denomReel*n.denomReel;
    double ni=numIm*n.denomIm+n.numIm*denomIm;
    int di=denomIm*n.denomIm;

    QString tRe=getResTypeRe(n,dr);
    QString tIm=getResTypeIm(n,ni,di);

    Numerique res(nr,ni,tRe,tIm,dr,di);

    return res;
}

Numerique Numerique::operator-(const Numerique& n)
{

    double nr=numReel*n.denomReel-n.numReel*denomReel;
    int dr=denomReel*n.denomReel;
    double ni=numIm*n.denomIm-n.numIm*denomIm;
    int di=denomIm*n.denomIm;

    QString tRe=getResTypeRe(n,dr);
    QString tIm=getResTypeIm(n,ni,di);

    Numerique res(nr,ni,tRe,tIm,dr,di);

    return res;
}


Numerique Numerique::operator*(const Numerique& n)
{
    double nr=(numReel*n.numReel);
    int dr=denomReel*n.denomReel;
    double ni=(numIm*n.numIm);
    int di=denomIm*n.denomIm;

    QString tRe=getResTypeRe(n,dr);
    QString tIm=getResTypeIm(n,ni,di);

    Numerique res(nr,ni,tRe,tIm,dr,di);

    return res;
}

Numerique Numerique::operator/(const Numerique& n)
{
    double nr=numReel*n.denomReel;
    int dr=denomReel*n.numReel;
    double ni=numIm*n.denomIm;
    int di=denomIm*n.numIm;

    QString tRe;
    QString tIm;

    if (typeRe=="entier" && n.typeRe=="entier")
    {
         tRe="rationnel";
    }
    else if (typeRe=="reel" || n.typeRe=="reel")
    {
         tRe="reel";
         nr=nr/dr;
         dr=1;
    }
    else//rationnel
    {
        tRe="rationnel";
    }

    if(ni==0) tIm="null";

    else if (typeIm=="entier" && n.typeIm=="entier")
    {
        tIm="rationnel";
    }
    else if (typeIm=="reel" || n.typeIm=="reel")
    {
        tIm="reel";
        ni=ni/di;
        di=1;
    }
    else
    {
        tIm="rationnel";
    }

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


QString Numerique::getResTypeRe(const Numerique& n,double dr)
{
    QString res;

    if(dr==1)//pas un rationnel
    {
        if (typeRe=="entier" && n.typeRe=="entier")
        {
             res="entier";
        }
        if (typeRe=="reel" || n.typeRe=="reel")
        {
             res="reel";
        }
    }
    else//rationnel
    {
        res="rationnel";
    }
    return res;

}

QString Numerique::getResTypeIm(const Numerique& n, double ni, double di)
{
    QString res;
    if(ni==0) return "null";
    if(di==1)//pas un rationnel
    {
        if (typeIm=="entier" && n.typeIm=="entier")
        {
            res="entier";
        }
        if (typeIm=="reel" || n.typeIm=="reel")
        {
            res="reel";
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
    si câ€™est le cas, on sort de la mÃ©thode */
    if (denomReel==0) return;
    /* utilisation de lâ€™algorithme dâ€™Euclide pour trouver le Plus Grand Commun
    Denominateur (PGCD) entre le numerateur et le denominateur */
    int a=numReel, b=denomReel;
    // on ne travaille quâ€™avec des valeurs positives...
    if (a<0) a=-a; if (b<0) b=-b;
    while(a!=b){ if (a>b) a=a-b; else b=b-a; }
    // on divise le numerateur et le denominateur par le PGCD=a
    numReel/=a; denomReel/=a;
    // si le denominateur est nÃ©gatif, on fait passer le signe - au numÃ©rateur
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


LitteraleManager& LitteraleManager::getInstance()
{
    if (handler.instance==nullptr) handler.instance=new LitteraleManager;
    return *handler.instance;
}

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

/*
double Numerique::getValue() const
{
    return 0;
}
*/

void LitteraleManager::agrandissementCapacite() {
    Litterale** newtab=new Litterale*[(nbMax+1)*2];
    for(unsigned int i=0; i<nb; i++) newtab[i]=exps[i];
    Litterale**  old=exps;
    exps=newtab;
    nbMax=(nbMax+1)*2;
    delete old;
}

Litterale& LitteraleManager::addLitterale(QString v){
    if (nb==nbMax) agrandissementCapacite();
    exps[nb++]=new Expression(v);
    return *exps[nb-1];
}

Litterale& LitteraleManager::addLitterale(Expression &v){
    if (nb==nbMax) agrandissementCapacite();
    exps[nb++]=new Expression(v);// appel au constructeur de recopie
    return *exps[nb-1];
}

Litterale& LitteraleManager::addLitterale(int v){
    if (nb==nbMax) agrandissementCapacite();
    exps[nb++]=new Numerique(v);
    return *exps[nb-1];
}

Litterale& LitteraleManager::addLitterale(double v){
    if (nb==nbMax) agrandissementCapacite();
    exps[nb++]=new Numerique(v);
    return *exps[nb-1];
}

Litterale& LitteraleManager::addLitterale(Numerique &v){
    if (nb==nbMax) agrandissementCapacite();
    exps[nb++]=new Numerique(v);// appel au constructeur de recopie
    return *exps[nb-1];
}

void LitteraleManager::removeLitterale(Litterale& e){
    unsigned int i=0;
    while(i<nb && exps[i]!=&e) i++;
    if (i==nb) throw ComputerException("elimination d'une Litterale inexistante");
    delete exps[i];
    i++;
    while(i<nb) { exps[i-1]=exps[i]; i++; }
    nb--;
}

LitteraleManager::~LitteraleManager(){
    for(unsigned int i=0; i<nb; i++) delete exps[i];
    delete[] exps;
}

Litterale& Item::getLitterale() const {
        if (exp==nullptr) throw ComputerException("Item : tentative d'acces a une Litterale inexistante");
        return *exp;
}


void Pile::agrandissementCapacite() {
    Item* newtab=new Item[(nbMax+1)*2];
    for(unsigned int i=0; i<nb; i++) newtab[i]=items[i];
    Item*  old=items;
    items=newtab;
    nbMax=(nbMax+1)*2;
    delete[] old;
}

void Pile::push(Litterale& e){
    if (nb==nbMax) agrandissementCapacite();
    items[nb].setLitterale(e);
    nb++;
    modificationEtat();
}

void Pile::pop(){
    nb--;
    items[nb].raz();
    modificationEtat();
}

void Pile::affiche(QTextStream& f) const{
    f<<"********************************************* \n";
    f<<"M : "<<message<<"\n";
    f<<"---------------------------------------------\n";
    for(unsigned int i=nbAffiche; i>0; i--) {
        if (i<=nb) f<<i<<": "<<items[nb-i].getLitterale().toString()<<"\n";
        else f<<i<<": \n";
    }
    f<<"---------------------------------------------\n";
}


Pile::~Pile(){
    delete[] items;
}

Litterale& Pile::top() const {

    if (nb==0) throw ComputerException("aucune Litterale sur la pile");
    return items[nb-1].getLitterale();
}

bool estUneExpression(const QString s)
{
    if( s[0]=='\'' && s[s.length()-1]=='\'' )
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
    if (s=="NOT") return true;
    if (s=="SWAP") return true;
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
    return false;
}

bool estUnOperateurSansArg(const QString s)
{
    if (s=="CLEAR") return true;
    return false;
}


/*
bool estUnOperateur(const QCharRef s)
{
    if (s=='+') return true;
    if (s=='-') return true;
    if (s=='*') return true;
    if (s=='/') return true;
    return false;
}*/

/*bool estUnNombre(const QString s)
{
   bool ok=false;
   s.toInt(&ok);
   return ok;
}*/

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


/*void Controleur::commande(const QString& c){
    if (estUnNombre(c)){
        expAff.push(expMng.addLitterale(c.toInt()));
    }else{

        if (estUnOperateur(c)){
            if (expAff.taille()>=2) {
                double v2=expAff.top().getValue();
                expMng.removeLitterale(expAff.top());
                expAff.pop();
                double v1=expAff.top().getValue();
                expMng.removeLitterale(expAff.top());
                expAff.pop();
                int res;
                if (c=="+") res=v1+v2;
                if (c=="-") res=v1-v2;
                if (c=="*") res=v1*v2;
                if (c=="/") {
                    if (v2!=0) res=v1/v2;
                    else {
                        expAff.setMessage("Erreur : division par zéro");
                        res=v1;
                    }
                }
                Litterale& e=expMng.addLitterale(res);
                expAff.push(e);
            }else{
                expAff.setMessage("Erreur : pas assez d'arguments");
            }
        }else expAff.setMessage("Erreur : commande inconnue");
    }
}*/

void Controleur::commande(const QString& c)
{
    QString s;
    int i=0, j=0;
    while(i < (c.length()))
        {
            if (c[0] != '\''){
                while(i < (c.length()-1) && !estUnOperateurBinaire(c[i]) && c[i]!=' ')
                {
                    i++;
                }
            }
            else {
                i++;
                while(i < (c.length()-1) && c[i]!='\'')
                {
                    i++;
                }
            }

        s = c.mid(j,i-j+1);

        if(estUnEntier(s))
        {
            expAff.push(expMng.addLitterale(s.toInt()));
        }

        else if(estUnReel(s))
            expAff.push(expMng.addLitterale(s.toDouble()));

        else if(estUneExpression(s))
                {
                    s=s.mid(1,s.length()-2);
                    expAff.push(expMng.addLitterale(s));
                }

        else if(estUnOperateurBinaire(s))
        {

            if (expAff.taille() >= 2)
            {
                try{

                    if(expAff.top().getType()=="Numerique")
                    {
                        Numerique v2=dynamic_cast<Numerique&>(expAff.top());
                        expMng.removeLitterale(expAff.top());
                        expAff.pop();

                        if(expAff.top().getType()=="Numerique")
                        {
                            Numerique v1=dynamic_cast<Numerique&>(expAff.top());
                            expMng.removeLitterale(expAff.top());
                            expAff.pop();

                            Numerique res(0);// on initialise res a zero


                            if (s == "+") res = v1 + v2;
                            if (s == "-") res = v1 - v2;
                            if (s == "*") res = v1 * v2;
                            if (s == "$")
                            {
                                if(v2.getTypeIm() != "null" || v1.getTypeIm() != "null")
                                {
                                    expAff.setMessage("Erreur : au moins une litterale est deja complexes");
                                    res = v1;
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
                                    expAff.setMessage("Erreur : division par zéro");
                                    res = v1;
                                }
                            }
                            if (s == "DIV")
                            {
                                if(v2.getTypeIm() == "null" || v1.getTypeIm() == "null" || v2.getTypeRe() == "entier" || v1.getTypeRe() == "entier")
                                {
                                    res = v1.operatorDIV(v2);
                                }

                                else
                                {
                                    expAff.setMessage("Erreur : au moins une litterale n'est pas entiere");
                                    res = v1;
                                }
                            }
                            if (s == "MOD")
                            {
                                if(v2.getTypeIm() == "null" || v1.getTypeIm() == "null" || v2.getTypeRe() == "entier" || v1.getTypeRe() == "entier")
                                {
                                    res = v1.operatorMOD(v2);
                                }

                                else
                                {
                                    expAff.setMessage("Erreur : au moins une litterale n'est pas entiere");
                                    res = v1;
                                }
                            }
                            if (s == "SWAP")
                            {
                                res=v1;
                                Litterale& l=expMng.addLitterale(v2);

                                expAff.push(l);

                            }

                            Litterale& e=expMng.addLitterale(res);

                            expAff.push(e);
                        } // if v1 numerique
                        else if(expAff.top().getType()=="Expression")
                        {
                            Expression v1=dynamic_cast<Expression&>(expAff.top());
                            expMng.removeLitterale(expAff.top());
                            expAff.pop();

                            Expression res("");

                            if (s == "SWAP")
                            {
                                res=v1;
                                Litterale& l=expMng.addLitterale(v2);

                                expAff.push(l);

                            }

                            Litterale& e=expMng.addLitterale(res);

                            expAff.push(e);
                        }// else v1 expression

                    }//if v2 numerique
                    else if(expAff.top().getType()=="Expression")
                    {
                        Expression v2=dynamic_cast<Expression&>(expAff.top());
                        expMng.removeLitterale(expAff.top());
                        expAff.pop();
                        if(expAff.top().getType()=="Expression")
                        {
                            Expression v1=dynamic_cast<Expression&>(expAff.top());
                            expMng.removeLitterale(expAff.top());
                            expAff.pop();

                            Expression res("");// on initialise res a zero


                            if (s == "+") res = v1 + v2;
                            if (s == "-") res = v1 - v2;
                            if (s == "*") res = v1 * v2;
                            if (s == "/") res = v1 / v2;
                            if (s == "AND") res = v1.operatorAND(v2);
                            if (s == "OR") res = v1.operatorOR(v2);
                            if (s == "NOT") res = v1.operatorNOT(v2);
                            if (s == "SWAP")
                            {
                                res=v1;
                                Litterale& l=expMng.addLitterale(v2);

                                expAff.push(l);

                            }

                            Litterale& e=expMng.addLitterale(res);

                            expAff.push(e);
                            }//if v1 expression



                            else if(expAff.top().getType()=="Numerique")
                            {
                                Numerique v1=dynamic_cast<Numerique&>(expAff.top());
                                expMng.removeLitterale(expAff.top());
                                expAff.pop();

                                Numerique res(0);

                                if (s == "SWAP")
                                {
                                    res=v1;
                                    Litterale& l=expMng.addLitterale(v2);

                                    expAff.push(l);
                                 }

                                Litterale& e=expMng.addLitterale(res);

                                expAff.push(e);
                            }//if v1 numerique

                    }// else v2 expression

                } //try
                catch(std::bad_cast& e) { expAff.setMessage(e.what()); }


            }// taille>=2
            else
            {
                expAff.setMessage("Erreur : pas assez d'arguments");
            }
        }
        else if(estUnOperateurUnaire(s))
            {

                if (expAff.taille() >= 1)
                {
                    try{
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
                        i++;
                        j = i;
                        continue;
                    }
                    Litterale& e=expMng.addLitterale(res);

                    expAff.push(e);
                    }
                    catch(std::bad_cast& e) { expAff.setMessage(e.what()); }

                    try{

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
                        i++;
                        j = i;
                        continue;
                    }

                    Litterale& e=expMng.addLitterale(res);

                    expAff.push(e);
                    }
                    catch(std::bad_cast& e)
                    {
                    expAff.setMessage(e.what());
                    }
                }
                else
                {
                    expAff.setMessage("Erreur : pas assez d'arguments");
                }
        }
        else if(estUnOperateurSansArg(s))
        {
            if (s == "CLEAR")
            {
                while(!expAff.estVide())
                {
                    expMng.removeLitterale(expAff.top());
                    expAff.pop();
                }
            }
        }

        else expAff.setMessage("Erreur : commande inconnue");

        i++;
        j = i;
    }
}
