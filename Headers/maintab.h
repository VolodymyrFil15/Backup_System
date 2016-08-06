#ifndef MAINTAB_H
#define MAINTAB_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QListView>
#include <QDir>
#include <QFileSystemModel>
#include <QPushButton>
#include <QLabel>
#include <QFileInfo>
#include "Headers/mainwindow.h"

class mainWnd;

class mainTab : public QWidget
{
       Q_OBJECT
public:
    mainTab(mainWnd *_par, QWidget * parent = 0);

public:
    mainWnd * par;
    QGridLayout *lay;

    QLabel *lb1;
    QLabel *lb2;

    QListView *lvFirst;
    QListView *lvSecond;

    QPushButton *levelUp1;
    QPushButton *levelUp2;

    QFileSystemModel *model;
public slots:
        void on_lvFirst_doubleClicked(const QModelIndex &index);
};

#endif // MAINTAB_H
