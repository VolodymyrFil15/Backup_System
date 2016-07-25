#ifndef SETTINGSTAB_H
#define SETTINGSTAB_H

#include <QObject>
#include <QWidget>
#include <QMessageBox>
#include <Headers/settingsGroupBox.h>

class settingsTab : public QWidget
{
    Q_OBJECT
public:
    explicit settingsTab(QWidget *parent = 0);

public:

    bool filesOpenBool = false;
    bool closeBool = false;

    settingsGroupBox *firstSGB;
    settingsGroupBox *secondSGB;

    QCheckBox *openFileCB;
    QCheckBox *closeCB;

    QGridLayout *lay;

signals:

public slots:
    void on_openFileCB_clicked();
    void on_closeCB_clicked();
};

#endif // SETTINGSTAB_H
