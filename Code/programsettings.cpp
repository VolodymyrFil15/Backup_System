#include "Headers/programsettings.h"

programSettings::programSettings(mainWnd *_par, QWidget *parent) : QWidget(parent)
{
    par = _par;
    translations << "English" << "Русский" << "Українська";
    openFileCheckBox = new QCheckBox(tr("Open files on double click"));
    closeCheckBox = new QCheckBox(tr("Close program after copying is finished"));
    layout = new QGridLayout(this);
    layout->addWidget(openFileCheckBox, 0, 0);
    layout->addWidget(closeCheckBox, 0, 1);
    languageLabel = new QLabel(tr("Choose language"));
    layout->addWidget(languageLabel, 1, 0);
    languageComboBox = new QComboBox(this);
    layout->addWidget(languageComboBox, 1, 1);
    setLanguageButton = new QPushButton(tr("OK"));
    layout->addWidget(setLanguageButton, 1, 2);
    languageComboBox->addItems(translations);
    connect(openFileCheckBox, SIGNAL(clicked(bool)), this, SLOT(onOpenFileCheckBoxClicked()));
    connect(closeCheckBox, SIGNAL(clicked(bool)), this, SLOT(onCloseCheckBoxClicked()));
    connect(languageComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(onLanguageComboBoxChanged(QString)));
}

void programSettings::onOpenFileCheckBoxClicked()
{
    par->fileOpenBool = openFileCheckBox->isChecked();
}

void programSettings::onCloseCheckBoxClicked()
{
    par->closeBool = closeCheckBox->isChecked();
}

void programSettings::onLanguageComboBoxChanged(QString postfix)
{
    if(QString::compare(postfix, "Русский") == 0)
    {
        emit languageChangeSignal("ru");
    }
    else if(QString::compare(postfix, "Українська") == 0)
    {
        emit languageChangeSignal("uk");
    }
    else
    {
        emit languageChangeSignal("en");
    }

}
