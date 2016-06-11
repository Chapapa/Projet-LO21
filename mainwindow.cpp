#include "mainwindow.h"


/**
 * \fn QComputer::QComputer(QWidget *parent):QWidget(parent)
 * \brief Constructeur
 */
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
    nbVuesPile = new QHBoxLayout();
    nbVuesPileLabel = new QLabel();
    getNbVuesPile = new QLineEdit();
    nbVuesPileLabel->setText("Nombre d'items à afficher:");
    nbVuesPile->addWidget(nbVuesPileLabel);
    nbVuesPile->addWidget(getNbVuesPile);
    paramCalc->addLayout(nbVuesPile);
    connect(getNbVuesPile,SIGNAL(returnPressed()),this,SLOT(changeNbViews()));

    // Vue sur les variables stockées
    fenetreVarStockees = new QWidget;
    fenetreVarStockees->setWindowTitle("Vue sur les variables");
    fenetreVarStockees->setFixedHeight(200);
    fenetreVarStockees->setFixedWidth(400);
    vueVarStockees = new QTableWidget(1, 2,fenetreVarStockees);
    vueVarStockees->horizontalHeader()->setVisible(false);
    vueVarStockees->horizontalHeader()->setStretchLastSection(true);
    vueVarStockees->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vueVarStockees->setRowHeight(0, 30);
    layoutVar = new QHBoxLayout(fenetreVarStockees);
    layoutModifier = new QVBoxLayout();
    for(unsigned int i = 1; i < 20; i++)
    {
        modifier[i] = NULL;
    }
    modifier[0] = new QPushButton("modifier");
    layoutVar->addWidget(vueVarStockees);
    layoutVar->addLayout(layoutModifier);
    layoutModifier->addWidget(modifier[0]);
    layoutVar->setAlignment(Qt::AlignBottom);
    vueVarStockees->setFixedHeight(30*(vueVarStockees->rowCount())+3);
    fenetreVarStockees->setFixedHeight(30*(vueVarStockees->rowCount())+20);

    connect(pile, SIGNAL(atomeAdded()),this, SLOT(updateEditVar()));


    //Fenetre d'édition d'une variable
    fenetreModifVar = new QWidget;
    fenetreModifVar->setWindowTitle("Editeur de variable");
    layoutModifVar = new QHBoxLayout(fenetreModifVar);
    layoutVVar = new QVBoxLayout();
    layoutVGetModifVar = new QVBoxLayout();
    nomVar = new QLabel("Nom de la variable:");
    valVar = new QLabel("Valeur de la variable:");
    getNomVar = new QLineEdit();
    getValVar = new QLineEdit();
    enregVar = new QPushButton("Enregistrer");
    layoutModifVar->addLayout(layoutVVar);
    layoutModifVar->addLayout(layoutVGetModifVar);
    layoutModifVar->addWidget(enregVar);
    layoutVVar->addWidget(nomVar);
    layoutVVar->addWidget(valVar);
    layoutVGetModifVar->addWidget(getNomVar);
    layoutVGetModifVar->addWidget(getValVar);
    layoutModifVar->setAlignment(Qt::AlignTop);
    connect(enregVar,SIGNAL(clicked()),this,SLOT(updateAtome()));


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

    // Toolbar
    menuOptions = new QMenu(this);
    menuEdition = new QMenu(this);
    undoRedo = new QMenu(this);

    tbar->addWidget(undoRedo);
    tbar->addWidget(menuOptions);
    tbar->addWidget(menuEdition);

    Undo = undoRedo->addAction("Annuler");
    Redo = undoRedo->addAction("Refaire");

    AfficherGraphicPad = menuOptions->addAction("Activer/Desactiver le clavier Graphique");
    AfficherGraphicPad->setCheckable(true);
    AfficherGraphicPad->setChecked(true);
    ActiverSons = menuOptions->addAction("Activer/Desactiver les sons d'erreur");
    beep = true;
    ActiverSons->setCheckable(true);
    ActiverSons->setChecked(true);
    ParamCalc = menuEdition->addAction("Paramètres du calculateur");

    EditerVar = menuEdition->addAction("Editer les variables stockées");

    Undo->setShortcut(tr("Ctrl+Z"));
    Redo->setShortcut(tr("Ctrl+Y"));
    ctrlZ = new QShortcut(tr("Ctrl+Z"), this);
    ctrlY = new QShortcut(tr("Ctrl+Y"), this);
    connect(ctrlZ, SIGNAL(activated()), this, SLOT(undo()));
    connect(ctrlY, SIGNAL(activated()), this, SLOT(redo()));

    connect(Undo, SIGNAL(triggered()), this, SLOT(undo()));
    connect(Redo, SIGNAL(triggered()), this, SLOT(redo()));
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
    controleur->initFile();
    controleur->loadFile(true);
    refresh();
}

/**
 * \fn void QComputer::updateProg()
 * \brief Mise a jour d un programme
 */
void QComputer::updateProg()
{
    pile->pop();
    controleur->commande(editProgT->toPlainText(), beep);
    refresh();
}


/**
 * \fn void QComputer::editProg()
 * \brief Edition d un programme
 */
void QComputer::editProg()
{
    editProgT->setText(pile->top().toString());
    if(fenetreEditProg->isHidden())
        fenetreEditProg->show();
    else
        fenetreEditProg->hide();
}


/**
 * \fn void QComputer::createGraphicPad()
 * \brief Creation du clavier graphique
 */
void QComputer::createGraphicPad()
{
    layout1 = new QHBoxLayout;
    un = new QPushButton("1",this);
    deux = new QPushButton("2",this);
    trois = new QPushButton("3",this);
    layout1->addWidget(un);
    layout1->addWidget(deux);
    layout1->addWidget(trois);

    layout2 = new QHBoxLayout;
    quatre = new QPushButton("4", this);
    cinq = new QPushButton("5", this);
    six = new QPushButton("6", this);
    layout2->addWidget(quatre);
    layout2->addWidget(cinq);
    layout2->addWidget(six);

    layout3 = new QHBoxLayout;
    sept = new QPushButton("7", this);
    huit = new QPushButton("8", this);
    neuf = new QPushButton("9", this);
    layout3->addWidget(sept);
    layout3->addWidget(huit);
    layout3->addWidget(neuf);

    layout4 = new QHBoxLayout;
    zero = new QPushButton("0", this);
    point = new QPushButton(".", this);

    correction = new QPushButton("Corr", this);
    correction->show();

    layout4->addWidget(zero);
    layout4->addWidget(point);
    layout4->addWidget(correction);


    layout5 = new QVBoxLayout;
    plus = new QPushButton("+", this);
    moins = new QPushButton("-", this);
    fois = new QPushButton("*", this);
    sur = new QPushButton("/", this);

    layout5->addWidget(plus);
    layout5->addWidget(moins);
    layout5->addWidget(fois);
    layout5->addWidget(sur);


    layoutG = new QVBoxLayout;
    layoutG->addLayout(layout1);
    layoutG->addLayout(layout2);
    layoutG->addLayout(layout3);
    layoutG->addLayout(layout4);

    layoutB = new QHBoxLayout;
    layoutB->addLayout(layoutG);
    layoutB->addLayout(layout5);

    layout6 = new QHBoxLayout;
    espace = new QPushButton("Espace");
    entree = new QPushButton("Entrée", this);
    entree->setDefault(true);
    layout6->addWidget(espace);
    layout6->addWidget(entree);

    layoutCalc = new QVBoxLayout;
    layoutCalc->addLayout(layoutB);
    layoutCalc->addLayout(layout6);
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
    mapper->setMapping( espace, " " );

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
    connect( espace, SIGNAL(clicked()), mapper, SLOT(map()) );
    connect( entree, SIGNAL(clicked()), this, SLOT(getNextCommande()) );

    connect(correction,SIGNAL(clicked()),this, SLOT( backspace()));


    connect( mapper, SIGNAL(mapped(QString)), this, SLOT(buttonClicked(QString)) );
}


/**
 * \fn void QComputer::changeNbViews()
 * \brief Parametrer le nombre d'items a afficher
 */
void QComputer::changeNbViews()
{
    pile->setNbItemsToAffiche(getNbVuesPile->text().toInt());
    vuePile->clear();
    unsigned int i = vuePile->rowCount()-1;
    while(pile->getNbItemsToAffiche() < (unsigned int)vuePile->rowCount())
    {
        vuePile->removeRow(i);
        i--;
    }
    while(pile->getNbItemsToAffiche() > (unsigned int)vuePile->rowCount())
    {
        vuePile->insertRow(i+1);
        i++;
    }
    QStringList nombres;
    for (i= pile->getNbItemsToAffiche(); i>0; i--)
    {
        QString str=QString::number(i);
        str+=":";
        nombres<<str;
    }
    vuePile->setVerticalHeaderLabels(nombres);
    for(i=0;i<pile->getNbItemsToAffiche();i++)
        vuePile->setItem(i,0, new QTableWidgetItem(""));
    refresh();
    getNbVuesPile->clear();
}

void QComputer::undo()
{
    controleur->undoCommand();
}

void QComputer::redo()
{
    controleur->redoCommand();
}

/**
 * \fn void QComputer::changeNbViewsVarEdit(unsigned int nbAtomes)
 * \brief Parametrer le nombre de variables a afficher
 */
void QComputer::changeNbViewsVarEdit(unsigned int nbAtomes)
{
    vueVarStockees->setFixedHeight(30*(vueVarStockees->rowCount()+1)+3);
    fenetreVarStockees->setFixedHeight(30*(vueVarStockees->rowCount()+1)+20);
    vueVarStockees->clear();
    unsigned int i = vueVarStockees->rowCount()-1;
    while(nbAtomes < (unsigned int)vueVarStockees->rowCount())
    {
        vueVarStockees->removeRow(i);
        layoutModifier->removeWidget(modifier[i]);
        if(modifier[i])
            delete modifier[i];
        i--;
    }
    i++;
    while(nbAtomes > (unsigned int)vueVarStockees->rowCount() && vueVarStockees->rowCount() < 20)
    {
        vueVarStockees->insertRow(i);
        modifier[i] = new QPushButton();
        layoutModifier->addWidget(modifier[i]);
        i++;
    }
    QStringList nombres;
    for (unsigned int i= nbAtomes; i>0; i--)
    {
        QString str=QString::number(i);
        str+=":";
        nombres<<str;
    }

    for(unsigned int i=0;i<nbAtomes;i++)
    {
        vueVarStockees->setItem(i,0, new QTableWidgetItem(""));
        vueVarStockees->setItem(i,1, new QTableWidgetItem(""));
    }
    vueVarStockees->setFixedHeight(30*(vueVarStockees->rowCount())+3);
    fenetreVarStockees->setFixedHeight(30*(vueVarStockees->rowCount())+20);
}

/**
 * \fn void QComputer::toggleParamCalcView()
 * \brief Afficher/masquer la fenetre d'edition des parametres du calculateur
 */
void QComputer::toggleParamCalcView()
{
    if(fenetreParamCalc->isHidden())
        fenetreParamCalc->show();
    else
        fenetreParamCalc->hide();
}

/**
 * \fn void QComputer::toggleEditerVarView()
 * \brief Afficher/masquer la fenetre de gestion/edition des variables stockees
 */
void QComputer::toggleEditerVarView()
{
    if(fenetreVarStockees->isHidden())
        fenetreVarStockees->show();
    else
        fenetreVarStockees->hide();
}

/**
 * \fn void QComputer::toggleBeep()
 * \brief activation/desactivation du bip sonore
 */
void QComputer::toggleBeep()
{
    beep = !beep;
}

/**
 * \fn void QComputer::toggleGraphicPad()
 * \brief Afficher/masquer le clavier
 */
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
        espace->show();
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
        espace->hide();
        correction->hide();
    }

}


/**
 * \fn const QString QComputer::text() const
 * \brief Retourne le texte entre dans la zone de commande
 */
const QString QComputer::text() const
{
    return commande->text();
}

/**
 * \fn void QComputer::buttonClicked( const QString &newText )
 * \brief Mettre a jour la commande en ajoutant la valeur du bouton sur lequel l'utilisateur clique
 */
void QComputer::buttonClicked( const QString &newText )
{
    commande->setText( commande->text() + newText );
}

/**
 * \fn void QComputer::setText( const QString &newText )
 * \brief Affecte la chaine de caractere en parametre a la commande
 */
void QComputer::setText( const QString &newText )
{
    if( newText == commande->text() )
        return;

    commande->text() = newText;
    commande->setText( commande->text() );

    emit textChanged( commande->text() );
}

/**
 * \fn void QComputer::refresh()
 * \brief Rafraichir le calculateur
 */
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

/**
 * \fn void QComputer::updateEditVar()
 * \brief Mettre a jour la vue dediee a la gestion des variables
 */
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
    QString atomeNom;
    tmp2 = controleur->getAtomes();
    for(unsigned int i = 0; i < nbAtomes - 1; i++)
    {
        tmp2++;
    }
    for(unsigned int i = 0; i < nbAtomes; i++)
    {
        atomeNom = "modifier ";
        atomeNom += (**tmp2).toString();
        modifier[i]->setText(atomeNom);
        connect(modifier[i], SIGNAL(clicked()),this,SLOT(modifierVar()));
        tmp2--;
    }
}

/**
 * \fn void QComputer::modifierVar()
 * \brief Modifier une variable stockee
 */
void QComputer::modifierVar()
{
    QPushButton* p = qobject_cast<QPushButton *>(sender());
    fenetreModifVar->show();
    unsigned int j;
    for(unsigned int i = 0; i < controleur->getNbAtomes(); i++)
    {
        if(modifier[i] == p)
            j = i;
    }
    j = controleur->getNbAtomes() - j - 1;
    //Atome* a;
    Atome** tmp = controleur->getAtomes();
    beingModified = tmp[j];
    getNomVar->setText(tmp[j]->getNom());
    getValVar->setText(tmp[j]->getLitterale().toString());
}

/**
 * \fn void QComputer::updateAtome()
 * \brief Mettre a jour un atome
 */
void QComputer::updateAtome()
{
    QString nom = getNomVar->text();
    QString val = getValVar->text();
    QString s = val + " " + nom + " STO" + " DROP";
    controleur->removeAtome(*beingModified);
    controleur->commande(s, beep);
    fenetreModifVar->hide();
}

/**
 * \fn void QComputer::getNextCommande()
 * \brief Passer a la commande suivante
 */
void QComputer::getNextCommande()
{
    pile->setMessage("");
    controleur->commande(commande->text(), beep);
    refresh();
    commande->clear();
}

/**
 * \fn void QComputer::backspace()
 * \brief Effacer le dernier caractere entre
 */
void QComputer::backspace()
{
    QString s=commande->text().mid(0,commande->text().length()-1);
    commande->setText( s );

    emit textChanged( commande->text() );
}
