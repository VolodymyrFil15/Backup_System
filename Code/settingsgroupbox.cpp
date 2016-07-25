#include "Headers/settingsGroupBox.h"

settingsGroupBox::settingsGroupBox(int num, QWidget *parent) : QGroupBox(parent)
{
        this->setTitle("Settings for folder " + QString::number(num));

        lay = new QGridLayout;
        _num = num;

        filesCB = new QCheckBox("Copy files from folder " + QString::number(num));
        foldersCB = new QCheckBox("Copy folders from folder " + QString::number(num));
        lay->addWidget(filesCB, 1, 1, 1, 4);
        lay->addWidget(foldersCB, 2, 1, 1, 4);

        minSizeCB = new QCheckBox("Min size for file to copy from folder " + QString::number(num));
        minSizeLE = new QLineEdit();
        minSizeBG = new QButtonGroup();
        minSizeByte = new QRadioButton("B");
        minSizeKByte = new QRadioButton("KB");
        minSizeMByte = new QRadioButton("MB");
        minSizeBG->addButton(minSizeByte);
        minSizeBG->addButton(minSizeKByte);
        minSizeBG->addButton(minSizeMByte);
        minSizeByte->setEnabled(minSizeBool);
        minSizeKByte->setEnabled(minSizeBool);
        minSizeMByte->setEnabled(minSizeBool);
        minSizeLE->setEnabled(minSizeBool);

        lay->addWidget(minSizeCB, 3, 1, 1, 4);
        lay->addWidget(minSizeLE, 4, 1);
        lay->addWidget(minSizeByte, 4, 2);
        lay->addWidget(minSizeKByte, 4, 3);
        lay->addWidget(minSizeMByte, 4, 4);

        maxSizeCB = new QCheckBox("max size for file to copy from folder " + QString::number(num));
        maxSizeLE = new QLineEdit();
        maxSizeBG = new QButtonGroup();
        maxSizeByte = new QRadioButton("B");
        maxSizeKByte = new QRadioButton("KB");
        maxSizeMByte = new QRadioButton("MB");
        maxSizeBG->addButton(maxSizeByte);
        maxSizeBG->addButton(maxSizeKByte);
        maxSizeBG->addButton(maxSizeMByte);
        maxSizeBool = maxSizeCB->isChecked();
        maxSizeByte->setEnabled(maxSizeBool);
        maxSizeKByte->setEnabled(maxSizeBool);
        maxSizeMByte->setEnabled(maxSizeBool);
        maxSizeLE->setEnabled(maxSizeBool);

        lay->addWidget(maxSizeCB, 5, 1, 1, 4);
        lay->addWidget(maxSizeLE, 6, 1);
        lay->addWidget(maxSizeByte, 6, 2);
        lay->addWidget(maxSizeKByte, 6, 3);
        lay->addWidget(maxSizeMByte, 6, 4);

        extensionsCB = new QCheckBox("Copy files with this extensions");
        extensionsLE = new QLineEdit;
        extensionsLE->setEnabled(extToCopyBool);

        lay->addWidget(extensionsCB, 7, 1, 1, 4);
        lay->addWidget(extensionsLE, 8, 1, 1, 4);

        connect(filesCB, QCheckBox::clicked, this, settingsGroupBox::on_filesCB_clicked);
        connect(foldersCB, QCheckBox::clicked, this, settingsGroupBox::on_foldersCB_clicked);
        connect(minSizeCB, QCheckBox::clicked, this, settingsGroupBox::on_minSizeCB_clicked);
        connect(maxSizeCB, QCheckBox::clicked, this, settingsGroupBox::on_maxSizeCB_clicked);
        connect(extensionsCB, QCheckBox::clicked, this, settingsGroupBox::on_extensionsCB_clicked);

        this->setLayout(lay);
}

void settingsGroupBox::on_filesCB_clicked()
{
    filesBool = filesCB->isChecked();
}
void settingsGroupBox::on_foldersCB_clicked()
{
    foldersBool = foldersCB->isChecked();
}
void settingsGroupBox::on_minSizeCB_clicked()
{
    minSizeBool = minSizeCB->isChecked();
    minSizeByte->setEnabled(minSizeBool);
    minSizeKByte->setEnabled(minSizeBool);
    minSizeMByte->setEnabled(minSizeBool);
    minSizeLE->setEnabled(minSizeBool);
}
void settingsGroupBox::on_maxSizeCB_clicked()
{
    maxSizeBool = maxSizeCB->isChecked();
    maxSizeByte->setEnabled(maxSizeBool);
    maxSizeKByte->setEnabled(maxSizeBool);
    maxSizeMByte->setEnabled(maxSizeBool);
    maxSizeLE->setEnabled(maxSizeBool);
}
void settingsGroupBox::on_extensionsCB_clicked()
{
    extToCopyBool = extensionsCB->isChecked();
    extensionsLE->setEnabled(extToCopyBool);
}
