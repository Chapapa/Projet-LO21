#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <windows.h>
#include "mainwindow.h"
/*
Command *Command::_commandList[];
Memento *Command::_mementoList[];
int Command::_numCommands = 0;
int Command::_highWater = 0;
*/
int main(int argc, char* argv[]){
    QApplication app(argc, argv);
    QComputer fenetre;
    fenetre.show();
    //Clavier graphique

    return app.exec();
}
