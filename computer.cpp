#include "computer.h"
#include <algorithm>



#include "computer.h"
#include <algorithm>

QString Numerique::getResTypeRe(const Numerique& n,double dr)
{
    QString tThisRe=this->getTypeRe();
    QString tnRe=n.getTypeRe();
    QString res;

    if(dr==1)//pas un rationnel
    {
        QString tThisRe=this->getTypeRe();
        QString tnRe=n.getTypeRe();
        if (tThisRe=="entier"&&tnRe=="entier")
        {
             res="entier";
        }
        if (tThisRe=="reel"||tnRe=="reel")
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
    QString tThisIm=this->getTypeIm();
    QString tnIm=n.getTypeIm();
    if(ni==0) return "null";
    if(di==1)//pas un rationnel
    {
        if (tThisIm=="entier"&&tnIm=="entier")
        {
            res="entier";
        }
        if (tThisIm=="reel"||tnIm=="reel")
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
            throw ComputerException("fraction exeption division par 0");
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
            throw ComputerException("fraction exeption division par 0");
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


QString  Numerique::toString() const
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


/*int getValue() const
{

}*/


void LitteraleManager::agrandissementCapacite() {
    Litterale** newtab=new Litterale*[(nbMax+1)*2];
    for(unsigned int i=0; i<nb; i++) newtab[i]=exps[i];
    Litterale**  old=exps;
    exps=newtab;
    nbMax=(nbMax+1)*2;
    delete old;
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



bool estUnOperateur(const QString s){
    if (s=="+") return true;
    if (s=="-") return true;
    if (s=="*") return true;
    if (s=="/") return true;
    return false;
}
/*
bool estUnOperateur(const QCharRef s){
    if (s=='+') return true;
    if (s=='-') return true;
    if (s=='*') return true;
    if (s=='/') return true;
    return false;
}*/

/*bool estUnNombre(const QString s){
   bool ok=false;
   s.toInt(&ok);
   return ok;
}*/

bool estUnEntier(const QString s){
   bool ok=false;
   s.toInt(&ok);
   return ok;
}


bool estUnReel(const QString s){
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
                int v2=expAff.top().getValue();
                expMng.removeLitterale(expAff.top());
                expAff.pop();
                int v1=expAff.top().getValue();
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
        while(i < (c.length()-1) && !estUnOperateur(c[i]) && c[i]!=' ')
        {
            i++;
        }


        //s=c.substr(j,i-j);
        s = c.mid(j,i-j+1);

        if(estUnEntier(s))
        {
            expAff.push(expMng.addLitterale(s.toInt()));
        }

        else if(estUnReel(s))
            expAff.push(expMng.addLitterale(s.toDouble()));

        else if(estUnOperateur(s))
        {
            if (expAff.taille() >= 2)
            {
                double v2=expAff.top().getValue();
                expMng.removeLitterale(expAff.top());
                expAff.pop();
                double v1=expAff.top().getValue();
                expMng.removeLitterale(expAff.top());
                expAff.pop();
                double res;
                if (c == "+") res = v1 + v2;
                if (c == "-") res = v1 - v2;
                if (c == "*") res = v1 * v2;
                if (c == "/") {
                    if (v2 != 0) res = v1 / v2;
                    else {
                        expAff.setMessage("Erreur : division par zéro");
                        res = v1;
                    }
                }
                Litterale& e=expMng.addLitterale(res);
                expAff.push(e);
            }else
            {
                expAff.setMessage("Erreur : pas assez d'arguments");
            }
        }
        else expAff.setMessage("Erreur : commande inconnue");

        i++;
        j = i;
    }
}
