/*#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H*/
#ifndef QCOMPUTER_H
#define QCOMPUTER_H
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QDebug>
#include <QSignalMapper>
#include <QLabel>
#include <QComboBox>
#include <QToolBar>
#include <QMenu>
#include <QAction>
#include <QMainWindow>
#include <QString>
#include <QIcon>
#include <windows.h>
#include "computer.h"


/**
 *  \class QComputer
 *  \brief Interface graphique de l'application
 */
class QComputer : public QWidget{
    Q_OBJECT
    //Main view
    QLineEdit* message;
    QTableWidget* vuePile;
    QLineEdit* commande;
    QVBoxLayout* couche;
    Pile* pile;
    Pile* pVarEdit;
    Pile* pProgEdit;
    Controleur* controleur;




    //Paramètres du calculateur
    QWidget* fenetreParamCalc;
    QVBoxLayout* paramCalc;
    QHBoxLayout* nbVuesPile;
    QLabel* nbVuesPileLabel;
    QLineEdit* getNbVuesPile;

    //Vue sur les variables stockées
    QWidget* fenetreVarStockees;
    QTableWidget* vueVarStockees;
    QHBoxLayout* layoutVar;
    QVBoxLayout* layoutModifier;
    QPushButton* modifier[20];

    //Fenetre d'édition d'une variable
    QWidget* fenetreModifVar;
    QVBoxLayout* layoutVVar;
    QVBoxLayout* layoutVGetModifVar;
    QHBoxLayout* layoutModifVar;
    QLabel* nomVar;
    QLabel* valVar;
    QLineEdit* getNomVar;
    QLineEdit* getValVar;
    QPushButton* enregVar;
    Atome* beingModified;

    //Editeur de programme
    QWidget* fenetreEditProg;
    QHBoxLayout* layoutEditProg;
    QTextEdit* editProgT;
    QPushButton* appliquer;

    //Toolbar
    QToolBar *tbar;
    QMenu *menuEdition;
    QMenu *menuOptions;
    QAction *AfficherGraphicPad;
    QAction *ActiverSons;
    QAction *ParamCalc;
    QAction *EditerVar;
    QAction *EditerProg;

    //Graphic pad
    QHBoxLayout* layout1;
    QHBoxLayout *layout2;
    QHBoxLayout *layout3;
    QHBoxLayout *layout4;
    QVBoxLayout *layout5;
    QHBoxLayout *layout6;
    QVBoxLayout *layoutG;
    QHBoxLayout *layoutB;
    QVBoxLayout *layoutCalc;
    QPushButton* zero;
    QPushButton* un;
    QPushButton* deux;
    QPushButton* trois;
    QPushButton* quatre;
    QPushButton* cinq;
    QPushButton* six;
    QPushButton* sept;
    QPushButton* huit;
    QPushButton* neuf;
    QPushButton* point;
    QPushButton* plus;
    QPushButton* moins;
    QPushButton* fois;
    QPushButton* sur;
    QPushButton* entree;
    QPushButton* espace;
    QPushButton* correction;
    bool beep;
public:
    explicit QComputer(QWidget *parent = 0);
    const QString text() const;
    void changeNbViewsVarEdit(unsigned int nbAtomes);
    void createGraphicPad();
public slots:
    void updateAtome();
    void toggleBeep();
    void toggleGraphicPad();
    void refresh();
    void getNextCommande();
    void setText(const QString &text);
    void changeNbViews();
    void toggleParamCalcView();
    void toggleEditerVarView();
    void editProg();
    void backspace();
    void updateProg();
    void updateEditVar();
    void modifierVar();
signals:
    void textChanged(const QString &text);
private slots:
    void buttonClicked(const QString &text);
};

#endif // QCOMPUTER_H

