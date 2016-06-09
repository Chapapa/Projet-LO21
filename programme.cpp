#include "programme.h"


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
