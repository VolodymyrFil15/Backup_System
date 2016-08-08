#include "Headers/settingstab.h"

copyingSettings::copyingSettings(mainWnd * _par, QWidget *parent) : QWidget(parent)
{
    par = _par;
    lay = new QGridLayout(this);

    firstSGB = new settingsGroupBox(1, this);
    secondSGB = new settingsGroupBox(2, this);

    lay->addWidget(firstSGB, 1, 1);
    lay->addWidget(secondSGB, 1, 2);
}
