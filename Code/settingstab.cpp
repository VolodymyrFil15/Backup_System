#include "Headers/settingstab.h"

settingsTab::settingsTab(QWidget *parent) : QWidget(parent)
{
    lay = new QGridLayout(this);

    firstSGB = new settingsGroupBox(1, this);
    secondSGB = new settingsGroupBox(2, this);

    openFileCB = new QCheckBox("Open files on double click");
    closeCB = new QCheckBox("Close program after copying is finished");

    lay->addWidget(firstSGB, 1, 1);
    lay->addWidget(secondSGB, 1, 2);
    lay->addWidget(openFileCB, 2, 1);
    lay->addWidget(closeCB, 2, 2);

    connect(openFileCB, QCheckBox::clicked, this, settingsTab::on_openFileCB_clicked);
    connect(closeCB, QCheckBox::clicked, this, settingsTab::on_closeCB_clicked);
}

void settingsTab::on_openFileCB_clicked()
{
    filesOpenBool = openFileCB->isChecked();
}

void settingsTab::on_closeCB_clicked()
{
    closeBool = closeCB->isChecked();
}
