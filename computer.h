/**
 * \file computer.h
 * \brief Déclarations des classes du calculateur
 */

#ifndef _COMPUTER_H
#define _COMPUTER_H

#include <QString>
#include <QTextStream>
#include <QObject>
#include <QDebug>
#include <windows.h>


using namespace std;

/**
 *  \class ComputerException
 *  \brief Gestion des Exception
 */
class ComputerException
{
    QString info;
public:
    ComputerException(const QString& str):info(str){}
    QString getInfo() const { return info; }
};



bool estUnOperateur(const QString s);
bool estUnOperateurBinaire(const QString s);
bool estUnOperateurUnaire(const QString s);
bool estUnNombre(const QString s);
bool estUneExpression(const QString s);
bool estUnProgramme(QString s);
bool estUnOperateurSansArg(const QString s);
bool estUnEntier(const QString s);
bool estUnReel(const QString s);
bool estUnRationnel(const QString c, QString s, int i);

QString RemoveSpaces(QString s);

void decompCommande(const QString& c,int &i, int &j);


#endif
