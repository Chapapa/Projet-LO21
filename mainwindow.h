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
#include "computer.h"

class QComputer : public QWidget{
    Q_OBJECT
    QLineEdit* message;
    QTableWidget* vuePile;
    QLineEdit* commande;
    QVBoxLayout* couche;
//    QComboBox* options;
    Pile* pile;
    Controleur* controleur;
    QHBoxLayout* layout1;
    QHBoxLayout *layout2;
    QHBoxLayout *layout3;
    QHBoxLayout *layout4;
    QVBoxLayout *layout5;
    QVBoxLayout *layoutG;
    QHBoxLayout *layoutB;
    QVBoxLayout *layout;
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
public:
    explicit QComputer(QWidget *parent = 0);
    const QString text() const;
public slots:
    void refresh();
    void getNextCommande();
    void setText(const QString &text);
signals:
    void textChanged(const QString &text);
private slots:
    void buttonClicked(const QString &text);
};

#endif // QCOMPUTER_H

