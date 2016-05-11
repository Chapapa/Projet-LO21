#include "mainwindow.h"


QComputer::QComputer(QWidget *parent):QWidget(parent)
{

    message= new QLineEdit(this);
    pile= new Pile();
    vuePile= new QTableWidget(pile->getNbItemsToAffiche(),1,this);
    commande= new QLineEdit(this);

    couche= new QVBoxLayout;
    couche->addWidget(message);
    couche->addWidget(vuePile);
    couche->addWidget(commande);
    setLayout(couche);


    controleur= new Controleur(LitteraleManager::getInstance(),*pile);

    setWindowTitle("UTComputer");
    message->setReadOnly(true);
    message->setText("Bienvenue");
    message->setStyleSheet("background:blake; color:white");

    vuePile->horizontalHeader()->setVisible(false);
    vuePile->horizontalHeader()->setStretchLastSection(true);

    QStringList nombres;
    for (unsigned int i= pile->getNbItemsToAffiche(); i>0; i--)
    {
        QString str=QString::number(i);
        str+=":";
        nombres<<str;
    }

    vuePile->setVerticalHeaderLabels(nombres);

   //ne pas ecrire dans vuepile
    vuePile->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect(commande,SIGNAL(returnPressed()),this,SLOT(getNextCommande()));
    connect(pile,SIGNAL(modificationEtat()),this,SLOT(refresh()));

    for(unsigned int i=0;i<pile->getNbItemsToAffiche();i++)
        vuePile->setItem(i,0, new QTableWidgetItem(""));



}

void QComputer::refresh()
{
    //MaJ du message
    message->setText(pile->getMessage());

    for(unsigned int i=0; i<pile->getNbItemsToAffiche();++i)
        vuePile->item(i,0)->setText("");

    unsigned int nb=0;
    for(Pile::iterator it=pile->begin(); it!=pile->end() && nb<pile->getNbItemsToAffiche();++it)
    {
        vuePile->item(pile->getNbItemsToAffiche()-nb-1,0)->setText((*it).toString());
        nb++;
    }
}

void QComputer::getNextCommande()
{
    pile->setMessage("");
    controleur->commande(commande->text());
    commande->clear();

}


