#include "mainwindow.h"


QComputer::QComputer(QWidget *parent):QWidget(parent)
{

    message= new QLineEdit(this);
    pile= new Pile();
    pVarEdit = new Pile();
    vuePile= new QTableWidget(pile->getNbItemsToAffiche(),1,this);
    commande= new QLineEdit(this);
    tbar = new QToolBar(this);

    couche= new QVBoxLayout;
    couche->addWidget(tbar);
    couche->addWidget(message);
    couche->addWidget(vuePile);
    couche->addWidget(commande);

    controleur= new Controleur(*(new LitteraleManager),*pile);

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

    // Paramètres du calculateur
    fenetreParamCalc = new QWidget;
    fenetreParamCalc->setWindowTitle("Paramètres du calculateur");
    fenetreParamCalc->setFixedHeight(200);
    fenetreParamCalc->setFixedWidth(400);
    paramCalc = new QVBoxLayout(fenetreParamCalc);
    nbVuesPile = new QHBoxLayout(fenetreParamCalc);
    nbVuesPileLabel = new QLabel(fenetreParamCalc);
    getNbVuesPile = new QLineEdit(fenetreParamCalc);
    nbVuesPileLabel->setText("Nombre d'items à afficher:");
    nbVuesPile->addWidget(nbVuesPileLabel);
    nbVuesPile->addWidget(getNbVuesPile);
    paramCalc->addLayout(nbVuesPile);
    connect(getNbVuesPile,SIGNAL(returnPressed()),this,SLOT(changeNbViews()));

    // Vue sur les variables stockées
    fenetreVarStockees = new QWidget;
    fenetreVarStockees->setWindowTitle("Editeur de variables");
    fenetreVarStockees->setFixedHeight(200);
    fenetreVarStockees->setFixedWidth(400);
    vueVarStockees = new QTableWidget(1, 2,fenetreVarStockees);
    vueVarStockees->horizontalHeader()->setVisible(false);
    vueVarStockees->horizontalHeader()->setStretchLastSection(true);


    // Editeur de programme
    fenetreEditProg = new QWidget;
    fenetreEditProg->setWindowTitle("Editeur de programme");
    fenetreEditProg->setFixedHeight(200);
    fenetreEditProg->setFixedWidth(400);
    layoutEditProg = new QHBoxLayout(fenetreEditProg);
    editProgT = new QTextEdit(fenetreEditProg);
    appliquer = new QPushButton("Enregistrer", fenetreEditProg);
    layoutEditProg->addWidget(editProgT);
    layoutEditProg->addWidget(appliquer);
    connect(pile, SIGNAL(edit()),this,SLOT(editProg()));
    connect(appliquer, SIGNAL(pressed()),this,SLOT(updateProg()));

    // Barre d'options
    menuOptions = new QMenu(this);
    menuEdition = new QMenu(this);

    tbar->addWidget(menuOptions);
    tbar->addWidget(menuEdition);

    AfficherGraphicPad = menuOptions->addAction("Activer/Desactiver le clavier Graphique");
    AfficherGraphicPad->setCheckable(true);
    AfficherGraphicPad->setChecked(true);
    ActiverSons = menuOptions->addAction("Activer/Desactiver les sons d'erreur");
    beep = true;
    ActiverSons->setCheckable(true);
    ActiverSons->setChecked(true);
    ParamCalc = menuOptions->addAction("Paramètres du calculateur");

    EditerVar = menuEdition->addAction("Editer les variables stockées");
    EditerProg = menuEdition->addAction("Editer les programmes stockés");


    connect(AfficherGraphicPad, SIGNAL(triggered()), this, SLOT(toggleGraphicPad()));
    connect(ParamCalc, SIGNAL(triggered()), this, SLOT(toggleParamCalcView()));
    connect(ActiverSons, SIGNAL(triggered()), this, SLOT(toggleBeep()));
    connect(EditerVar, SIGNAL(triggered()), this, SLOT(toggleEditerVarView()));


    // Graphic Pad
    createGraphicPad();

    connect( commande, SIGNAL(textChanged(QString)), this, SLOT(setText(QString)) );
    QLabel label;
    couche->addWidget( &label );
    QObject::connect( this, SIGNAL(textChanged(QString)), &label, SLOT(setText(QString)) );
}

void QComputer::updateProg()
{
    pile->pop();
    controleur->commande(editProgT->toPlainText(), beep);
    refresh();
}

void QComputer::editProg()
{
    editProgT->setText(pile->top().toString());
    if(fenetreEditProg->isHidden())
        fenetreEditProg->show();
    else
        fenetreEditProg->hide();
}

void QComputer::createGraphicPad()
{
    layout1 = new QHBoxLayout;
    un = new QPushButton("1",this);
    un->show();
    deux = new QPushButton("2",this);
    deux->show();
    trois = new QPushButton("3",this);
    trois->show();
    layout1->addWidget(un);
    layout1->addWidget(deux);
    layout1->addWidget(trois);

    layout2 = new QHBoxLayout;
    quatre = new QPushButton("4", this);
    quatre->show();
    cinq = new QPushButton("5", this);
    cinq->show();
    six = new QPushButton("6", this);
    six->show();
    layout2->addWidget(quatre);
    layout2->addWidget(cinq);
    layout2->addWidget(six);

    layout3 = new QHBoxLayout;
    sept = new QPushButton("7", this);
    sept->show();
    huit = new QPushButton("8", this);
    huit->show();
    neuf = new QPushButton("9", this);
    neuf->show();
    layout3->addWidget(sept);
    layout3->addWidget(huit);
    layout3->addWidget(neuf);

    layout4 = new QHBoxLayout;
    zero = new QPushButton("0", this);
    zero->show();
    point = new QPushButton(".", this);
    point->show();

    correction = new QPushButton("Corr", this);
    correction->show();

    layout4->addWidget(zero);
    layout4->addWidget(point);
    layout4->addWidget(correction);


    layout5 = new QVBoxLayout;
    plus = new QPushButton("+", this);
    plus->show();
    moins = new QPushButton("-", this);
    moins->show();
    fois = new QPushButton("*", this);
    fois->show();
    sur = new QPushButton("/", this);
    sur->show();
    entree = new QPushButton("Entrée", this);
    entree->show();
    entree->setDefault(true);
    layout5->addWidget(plus);
    layout5->addWidget(moins);
    layout5->addWidget(fois);
    layout5->addWidget(sur);
    layout5->addWidget(entree);

    layoutG = new QVBoxLayout;
    layoutG->addLayout(layout1);
    layoutG->addLayout(layout2);
    layoutG->addLayout(layout3);
    layoutG->addLayout(layout4);

    layoutB = new QHBoxLayout;
    layoutB->addLayout(layoutG);
    layoutB->addLayout(layout5);

    layoutCalc = new QVBoxLayout;
    layoutCalc->addLayout(layoutB);
    couche->addLayout(layoutCalc);
    setLayout(couche);

    QSignalMapper *mapper = new QSignalMapper( this );

    mapper->setMapping( zero, "0" );
    mapper->setMapping( un, "1" );
    mapper->setMapping( deux, "2" );
    mapper->setMapping( trois, "3" );
    mapper->setMapping( quatre, "4" );
    mapper->setMapping( cinq, "5" );
    mapper->setMapping( six, "6" );
    mapper->setMapping( sept, "7" );
    mapper->setMapping( huit, "8" );
    mapper->setMapping( neuf, "9" );
    mapper->setMapping( point, "." );
    mapper->setMapping( plus, "+" );
    mapper->setMapping( moins, "-" );
    mapper->setMapping( fois, "*" );
    mapper->setMapping( sur, "/" );

    connect( zero, SIGNAL(clicked()), mapper, SLOT(map()) );
    connect( un, SIGNAL(clicked()), mapper, SLOT(map()) );
    connect( deux, SIGNAL(clicked()), mapper, SLOT(map()) );
    connect( trois, SIGNAL(clicked()), mapper, SLOT(map()) );
    connect( quatre, SIGNAL(clicked()), mapper, SLOT(map()) );
    connect( cinq, SIGNAL(clicked()), mapper, SLOT(map()) );
    connect( six, SIGNAL(clicked()), mapper, SLOT(map()) );
    connect( sept, SIGNAL(clicked()), mapper, SLOT(map()) );
    connect( huit, SIGNAL(clicked()), mapper, SLOT(map()) );
    connect( neuf, SIGNAL(clicked()), mapper, SLOT(map()) );
    connect( point, SIGNAL(clicked()), mapper, SLOT(map()) );
    connect( plus, SIGNAL(clicked()), mapper, SLOT(map()) );
    connect( moins, SIGNAL(clicked()), mapper, SLOT(map()) );
    connect( fois, SIGNAL(clicked()), mapper, SLOT(map()) );
    connect( sur, SIGNAL(clicked()), mapper, SLOT(map()) );
    connect( entree, SIGNAL(clicked()), this, SLOT(getNextCommande()) );

    connect(correction,SIGNAL(clicked()),this, SLOT( backspace()));


    connect( mapper, SIGNAL(mapped(QString)), this, SLOT(buttonClicked(QString)) );
}

void QComputer::changeNbViews()
{
    pile->setNbItemsToAffiche(getNbVuesPile->text().toInt());
    //Destruction de la vue pour en créer une avec le bon nombre de lignes d'affichage
    couche->removeWidget(vuePile);
    delete vuePile;
    vuePile = new QTableWidget(pile->getNbItemsToAffiche(),1,this);
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

    for(unsigned int i=0;i<pile->getNbItemsToAffiche();i++)
        vuePile->setItem(i,0, new QTableWidgetItem(""));
    remakeCalc();
    refresh();
    getNbVuesPile->clear();
}

void QComputer::changeNbViewsVarEdit(unsigned int nbAtomes)
{
    //Destruction de la vue pour en créer une avec le bon nombre de lignes d'affichage
    couche->removeWidget(vueVarStockees);
    delete vueVarStockees;
    vueVarStockees = new QTableWidget(nbAtomes,2,fenetreVarStockees);
    vueVarStockees->horizontalHeader()->setVisible(false);
    vueVarStockees->horizontalHeader()->setStretchLastSection(true);
    QStringList nombres;
    for (unsigned int i= nbAtomes; i>0; i--)
    {
        QString str=QString::number(i);
        str+=":";
        nombres<<str;
    }

    vueVarStockees->setVerticalHeaderLabels(nombres);

    //ne pas ecrire dans vuepile
    vueVarStockees->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(unsigned int i=0;i<nbAtomes;i++)
    {
        vueVarStockees->setItem(i,0, new QTableWidgetItem(""));
        vueVarStockees->setItem(i,1, new QTableWidgetItem(""));
    }
}

void QComputer::remakeCalc()
{
    couche->removeWidget(commande);

    layout1->removeWidget(un);
    layout1->removeWidget(deux);
    layout1->removeWidget(trois);

    layout2->removeWidget(quatre);
    layout2->removeWidget(cinq);
    layout2->removeWidget(six);

    layout3->removeWidget(sept);
    layout3->removeWidget(huit);
    layout3->removeWidget(neuf);


    layout4->removeWidget(zero);
    layout4->removeWidget(point);
    layout4->removeWidget(correction);

    layout5->removeWidget(plus);
    layout5->removeWidget(moins);
    layout5->removeWidget(fois);
    layout5->removeWidget(sur);
    layout5->removeWidget(entree);

    delete layout1;
    delete layout2;
    delete layout3;
    delete layout4;
    delete layout5;
    delete layoutG;
    delete layoutB;
    delete layoutCalc;

    couche->addWidget(vuePile);
    couche->addWidget(commande);

    layout1 = new QHBoxLayout;
    layout1->addWidget(un);
    layout1->addWidget(deux);
    layout1->addWidget(trois);

    layout2 = new QHBoxLayout;
    layout2->addWidget(quatre);
    layout2->addWidget(cinq);
    layout2->addWidget(six);

    layout3 = new QHBoxLayout;
    layout3->addWidget(sept);
    layout3->addWidget(huit);
    layout3->addWidget(neuf);

    layout4 = new QHBoxLayout;
    layout4->addWidget(zero);
    layout4->addWidget(point);
    layout4->addWidget(correction);


    layout5 = new QVBoxLayout;
    entree->setDefault(true);
    layout5->addWidget(plus);
    layout5->addWidget(moins);
    layout5->addWidget(fois);
    layout5->addWidget(sur);
    layout5->addWidget(entree);

    layoutG = new QVBoxLayout;
    layoutG->addLayout(layout1);
    layoutG->addLayout(layout2);
    layoutG->addLayout(layout3);
    layoutG->addLayout(layout4);

    layoutB = new QHBoxLayout;
    layoutB->addLayout(layoutG);
    layoutB->addLayout(layout5);

    layoutCalc = new QVBoxLayout;
    layoutCalc->addLayout(layoutB);
    couche->addLayout(layoutCalc);
}

void QComputer::toggleParamCalcView()
{
    if(fenetreParamCalc->isHidden())
        fenetreParamCalc->show();
    else
        fenetreParamCalc->hide();
}

void QComputer::toggleEditerVarView()
{
    updateEditVar();
    if(fenetreVarStockees->isHidden())
        fenetreVarStockees->show();
    else
        fenetreVarStockees->hide();
}

void QComputer::toggleBeep()
{
    beep = !beep;
}

void QComputer::toggleGraphicPad()
{
    if(plus->isHidden())
    {
        zero->show();
        un->show();
        deux->show();
        trois->show();
        quatre->show();
        cinq->show();
        six->show();
        sept->show();
        huit->show();
        neuf->show();
        point->show();
        plus->show();
        moins->show();
        fois->show();
        sur->show();
        entree->show();
        correction->show();
    }
    else
    {
        zero->hide();
        un->hide();
        deux->hide();
        trois->hide();
        quatre->hide();
        cinq->hide();
        six->hide();
        sept->hide();
        huit->hide();
        neuf->hide();
        point->hide();
        plus->hide();
        moins->hide();
        fois->hide();
        sur->hide();
        entree->hide();
        correction->hide();
    }

}

const QString QComputer::text() const
{
    return commande->text();
}

void QComputer::buttonClicked( const QString &newText )
{
    commande->setText( commande->text() + newText );
}

void QComputer::setText( const QString &newText )
{
    if( newText == commande->text() )
        return;

    commande->text() = newText;
    commande->setText( commande->text() );

    emit textChanged( commande->text() );
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

void QComputer::updateEditVar()
{
    unsigned int nbAtomes = controleur->getNbAtomes();
    changeNbViewsVarEdit(nbAtomes);

    for(unsigned int i = 0; i < nbAtomes; i++)
    {
        vueVarStockees->item(i,0)->setText("");
        vueVarStockees->item(i,1)->setText("");
    }
    Atome** tmp2 = controleur->getAtomes();

    for(unsigned int j = 0; j < nbAtomes; j++)
    {
        vueVarStockees->item(nbAtomes-j-1,0)->setText((**tmp2).toString());
        vueVarStockees->item(nbAtomes-j-1,1)->setText((**tmp2).getLitterale().toString());
        tmp2++;
    }
}

void QComputer::getNextCommande()
{
    pile->setMessage("");
    controleur->commande(commande->text(), beep);
    refresh();
    commande->clear();
}

void QComputer::backspace()
{
    QString s=commande->text().mid(0,commande->text().length()-1);
    commande->setText( s );

    emit textChanged( commande->text() );
}
