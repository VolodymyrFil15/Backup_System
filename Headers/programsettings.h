#ifndef PROGRAMSETTINGS_H
#define PROGRAMSETTINGS_H

#include <QObject>
#include <QWidget>
#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>
#include "Headers/mainwindow.h"
#include <QStringList>

class programSettings : public QWidget
{
    Q_OBJECT
public:
    explicit programSettings(mainWnd *_par, QWidget *parent = 0);

    mainWnd *par;
    QCheckBox *openFileCheckBox;
    QCheckBox *closeCheckBox;
    QGridLayout *layout;
    QComboBox *languageComboBox;
    QLabel *languageLabel;
    QPushButton *setLanguageButton;
    QStringList translations;

signals:
    void languageChangeSignal(QString postfix);

public slots:
    void onOpenFileCheckBoxClicked();
    void onCloseCheckBoxClicked();
    void onLanguageComboBoxChanged(QString postfix);
};

#endif // PROGRAMSETTINGS_H
