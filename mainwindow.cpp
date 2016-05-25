#include "mainwindow.h"


QComputer::QComputer(QWidget *parent):QWidget(parent)
{

    message= new QLineEdit(this);
    pile= new Pile();
    vuePile= new QTableWidget(pile->getNbItemsToAffiche(),1,this);
    commande= new QLineEdit(this);
    tbar = new QToolBar(this);

    couche= new QVBoxLayout;
    couche->addWidget(tbar);
    couche->addWidget(message);
    couche->addWidget(vuePile);
    couche->addWidget(commande);


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
    connect(ActiverSons, SIGNAL(triggered()), this, SLOT(toggleBeep()));



    // Graphic Pad

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
    layout4->addWidget(zero);
    layout4->addWidget(point);


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

    layout = new QVBoxLayout;
    layout->addLayout(layoutB);
    couche->addLayout(layout);
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

    connect( mapper, SIGNAL(mapped(QString)), this, SLOT(buttonClicked(QString)) );
    connect( commande, SIGNAL(textChanged(QString)), this, SLOT(setText(QString)) );
    QLabel label;
    couche->addWidget( &label );
    QObject::connect( this, SIGNAL(textChanged(QString)), &label, SLOT(setText(QString)) );
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

void QComputer::getNextCommande()
{
    pile->setMessage("");
    controleur->commande(commande->text(), beep);
    commande->clear();
}

