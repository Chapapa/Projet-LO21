#include <algorithm>
#include "computer.h"


void decompCommande(const QString& c,int &i, int &j);


/**
 * \fn QString RemoveSpaces(QString s)
 * \brief La fonction enleve les espaces dans les expressions entrées par l'utilisateur
 *
 * \param s Expression entree par l'utilisateur

 * \return La fonction retourne la chaine de caractere sans espaces
 */
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





/**
 * \fn bool estUneExpression(const QString s)
 * \brief Teste si la chaine passee en argument est une expression
 * \param s QString a tester
 */
bool estUneExpression(const QString s)
{
    if( s[0]=='\'' && s[s.length()-1]=='\'' )
        return true;
    return false;
}

/**
 * \fn bool estUnProgramme(QString s)
 * \brief Teste si la chaine passee en argument est un programme
 * \param s QString a tester
 */
bool estUnProgramme(QString s)
{
    if( s[0]=='[' && s[s.length()-1]==']' )
        return true;
    return false;
}

/**
 * \fn bool estUnOperateurBinaire(const QString s)
 * \brief Teste si la chaine passee en argument est un operateur binaire
 * \param s QString a tester
 */
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
/**
 * \fn bool estUnOperateurUnaire(const QString s)
 * \brief Teste si la chaine passee en argument est un operateur unaire
 * \param s QString a tester
 */
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

/**
 * \fn bool estUnOperateurSansArg(const QString s)
 * \brief Teste si la chaine passee en argument est un operateur qui ne prend pas d'argument
 * \param s QString a tester
 */
bool estUnOperateurSansArg(const QString s)
{
    if (s=="CLEAR") return true;
    if (s=="UNDO") return true;
    if (s=="REDO") return true;
    if (s=="LASTARGS") return true;
    return false;
}
/**
 * \fn bool estUnOperateur(const QString s)
 * \brief Teste si la chaine passee en argument est un operateur
 * \param s QString a tester
 */
bool estUnOperateur(const QString s)
{
    return(estUnOperateurBinaire(s) || estUnOperateurSansArg(s) || estUnOperateurUnaire(s));
}
/**
 * \fn bool estUnEntier(const QString s)
 * \brief Teste si la chaine passee en argument est un entier
 * \param s QString a tester
 */
bool estUnEntier(const QString s)
{
   bool ok=false;
   s.toInt(&ok);
   return ok;
}
/**
 * \fn bool estUnReel(const QString s)
 * \brief Teste si la chaine passee en argument est un reel
 * \param s QString a tester
 */
bool estUnReel(const QString s)
{
   bool ok=false;
   s.toDouble(&ok);
   return ok;
}
/**
 * \fn bool estUnRationnel(const QString c, QString s, int i)
 * \brief Teste si la chaine passee en argument est un entier
 * \param c Chaine de caractere totale
 * \param s Sous chaine situee avant i
 * \param i indice ou on devrait rencontrer '/' si il s'agit d'un rationnel
 */
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

/**
 * \fn void decompCommande(const QString& c,int &i, int &j)
 * \brief Détermine les i et j pour décomposer la commande reçue
 * \param c Chaine a decomposer
 * \param i Fin de la sous chaine
 * \param j Debut de la sous chaine
 */
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

