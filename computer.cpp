#include "computer.h"
#include <algorithm>



void Numerique::simplification(){
// si le numerateur est 0, le denominateur prend la valeur 1
if (numReel==0) { denomReel=1; return; }
/* un denominateur ne devrait pas être 0;
si c’est le cas, on sort de la méthode */
if (denomReel==0) return;
/* utilisation de l’algorithme d’Euclide pour trouver le Plus Grand Commun
Denominateur (PGCD) entre le numerateur et le denominateur */
int a=numReel, b=denomReel;
// on ne travaille qu’avec des valeurs positives...
if (a<0) a=-a; if (b<0) b=-b;
while(a!=b){ if (a>b) a=a-b; else b=b-a; }
// on divise le numerateur et le denominateur par le PGCD=a
numReel/=a; denomReel/=a;
// si le denominateur est négatif, on fait passer le signe - au denominateur
if (denomReel<0) { denomReel=-denomReel; numReel=-numReel; }
}

void Numerique::setRationel(int n,int d)
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
    simplification();

}



LitteraleManager::Handler LitteraleManager::handler=LitteraleManager::Handler();


LitteraleManager& LitteraleManager::getInstance(){
    if (handler.instance==nullptr) handler.instance=new LitteraleManager;
    return *handler.instance;
}

void LitteraleManager::libererInstance(){
    delete handler.instance;
    handler.instance=nullptr;
}


/*QString  Numerique::toString() const {
    return QString::number(value);
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

bool estUnNombre(const QString s){
   bool ok=false;
   s.toInt(&ok);
   return ok;
}


void Controleur::commande(const QString& c){
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
                        expAff.setMessage("Erreur : division par zÃ©ro");
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
}


