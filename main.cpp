#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "mainwindow.h"

int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    QComputer fenetre;
    fenetre.show();

    /*
    // clavier graphique
    QWidget Pad;

    QHBoxLayout *layout0 = new QHBoxLayout;
    QLineEdit* commande = new QLineEdit(&Pad);
    commande->show();
    layout0->addWidget(commande);

    QHBoxLayout *layout1 = new QHBoxLayout;
    QPushButton* un = new QPushButton("1",&Pad);
    un->show();
    QPushButton* deux = new QPushButton("2",&Pad);
    deux->show();
    QPushButton* trois = new QPushButton("3",&Pad);
    trois->show();
    layout1->addWidget(un);
    layout1->addWidget(deux);
    layout1->addWidget(trois);

    QHBoxLayout *layout2 = new QHBoxLayout;
    QPushButton* quatre = new QPushButton("4", &Pad);
    quatre->show();
    QPushButton* cinq = new QPushButton("5", &Pad);
    cinq->show();
    QPushButton* six = new QPushButton("6", &Pad);
    six->show();
    layout2->addWidget(quatre);
    layout2->addWidget(cinq);
    layout2->addWidget(six);

    QHBoxLayout *layout3 = new QHBoxLayout;
    QPushButton* sept = new QPushButton("7", &Pad);
    sept->show();
    QPushButton* huit = new QPushButton("8", &Pad);
    huit->show();
    QPushButton* neuf = new QPushButton("9", &Pad);
    neuf->show();
    layout3->addWidget(sept);
    layout3->addWidget(huit);
    layout3->addWidget(neuf);

    QHBoxLayout *layout4 = new QHBoxLayout;
    QPushButton* zero = new QPushButton("0", &Pad);
    zero->show();
    layout4->addWidget(zero);


    QVBoxLayout *layout5 = new QVBoxLayout;
    QPushButton* plus = new QPushButton("+", &Pad);
    plus->show();
    QPushButton* moins = new QPushButton("-", &Pad);
    moins->show();
    QPushButton* fois = new QPushButton("*", &Pad);
    fois->show();
    QPushButton* sur = new QPushButton("/", &Pad);
    sur->show();
    QPushButton* entree = new QPushButton("Entrée", &Pad);
    entree->show();
    layout5->addWidget(plus);
    layout5->addWidget(moins);
    layout5->addWidget(fois);
    layout5->addWidget(sur);
    layout5->addWidget(entree);

    QVBoxLayout *layoutG = new QVBoxLayout;
    layoutG->addLayout(layout1);
    layoutG->addLayout(layout2);
    layoutG->addLayout(layout3);
    layoutG->addLayout(layout4);

    QHBoxLayout *layoutB = new QHBoxLayout;
    layoutB->addLayout(layoutG);
    layoutB->addLayout(layout5);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(layout0);
    layout->addLayout(layoutB);


    Pad.setLayout(layout);
    Pad.show();
    */
    return app.exec();
}
