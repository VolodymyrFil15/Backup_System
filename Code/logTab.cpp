#include "Headers/logTab.h"

logTab::logTab(QWidget *parent) : QWidget(parent)
{
    lay = new QGridLayout;
    logHolder = new QTextBrowser();
    lay->addWidget(logHolder);
    this->setLayout(lay);
}
