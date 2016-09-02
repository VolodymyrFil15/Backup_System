#ifndef SETTINGS_H
#define SETTINGS_H

#endif // SETTINGS_H

#include <QCheckBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QGroupBox>
#include <QLineEdit>
#include <QTranslator>
#include <QApplication>
#include <QGridLayout>

class settingsGroupBox : public QGroupBox
{
public:

    bool filesBool = false;
    bool foldersBool = false;
    bool minSizeBool = false;
    bool maxSizeBool = false;
    bool extToCopyBool = false;

    QGridLayout *lay;

    QCheckBox *filesCB;
    QCheckBox *foldersCB;

    QCheckBox *minSizeCB;
    QLineEdit *minSizeLE;
    QButtonGroup *minSizeBG;
    QRadioButton *minSizeByte;
    QRadioButton *minSizeKByte;
    QRadioButton *minSizeMByte;

    QCheckBox *maxSizeCB;
    QLineEdit *maxSizeLE;
    QButtonGroup *maxSizeBG;
    QRadioButton *maxSizeByte;
    QRadioButton *maxSizeKByte;
    QRadioButton *maxSizeMByte;

    QCheckBox *extensionsCB;
    QLineEdit *extensionsLE;

    QTranslator *translator;
    int _num;

public slots:
    void on_extensionsCB_clicked();
    void on_maxSizeCB_clicked();
    void on_minSizeCB_clicked();
    void on_filesCB_clicked();
    void on_foldersCB_clicked();

public:
    settingsGroupBox(int num, QWidget *parent = 0);
};
