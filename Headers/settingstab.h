#ifndef SETTINGSTAB_H
#define SETTINGSTAB_H

#include <QObject>
#include <QWidget>
#include <QMessageBox>
#include <Headers/settingsGroupBox.h>
#include "Headers/mainwindow.h"

class mainWnd;

class copyingSettings : public QWidget
{
    Q_OBJECT
public:
    copyingSettings(mainWnd *_par, QWidget *parent = 0);

public:
    mainWnd *par;

    settingsGroupBox *firstSGB;
    settingsGroupBox *secondSGB;
    QGridLayout *lay;

};

#endif // SETTINGSTAB_H
