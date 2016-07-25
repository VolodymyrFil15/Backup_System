#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QListView>
#include <QTabWidget>
#include <QProgressBar>
#include <QTime>
#include <QDebug>
#include <QUrl>
#include <QDesktopServices>
#include <QMessageBox>
#include "Headers/maintab.h"
#include "Headers/settingstab.h"
#include "Headers/logTab.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    QTime *time;
    QPushButton *syncBtn;
    QTabWidget *tabs;
    QGridLayout *globalLayout;
    QProgressBar *progressBar;
    mainTab *firstTab;
    settingsTab *secondTab;
    logTab *thirdTab;

public:
    int countSize(QLineEdit *inputLine, QButtonGroup *buttons);
public slots:

};

#endif // MAINWINDOW_H
