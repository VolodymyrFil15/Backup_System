#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QEvent>
#include <QApplication>
#include <QGridLayout>
#include <QPushButton>
#include <QListView>
#include <QTabWidget>
#include <QProgressBar>
#include <QTime>
#include <QDebug>
#include <QUrl>
#include <QThread>
#include <QDesktopServices>
#include <QMessageBox>
#include <QTranslator>
#include "Headers/maintab.h"
#include "Headers/settingstab.h"
#include "Headers/logTab.h"
#include "Headers/secondthread.h"
#include "Headers/programsettings.h"

class mainTab;
class copyingSettings;
class secondThread;
class programSettings;
class mainWnd : public QWidget
{
    Q_OBJECT

public:
    mainWnd(QWidget *parent = 0);
    ~mainWnd();

public:
    bool fileOpenBool = false;
    bool closeBool = false;
    QTime *time;
    QDir sDir, dDir;
    QFileInfoList diffList, diffList1;
    QPushButton *syncBtn;
    QTabWidget *tabs;
    QGridLayout *globalLayout;
    QProgressBar *progressBar;
    mainTab *firstTab;
    copyingSettings *copyingSettingsTab;
    logTab *thirdTab;
    programSettings *programSettingsTab;
    QString version;
    QTranslator *translator;

    quint64 curSize = 0;
    quint64 sumSize = 0;
    int minFrom1Int = 0;
    int minFrom2Int = 0;
    int maxFrom1Int = 0;
    int maxFrom2Int = 0;

    QStringList extensionsFrom1;
    QStringList extensionsFrom2;
    secondThread *rthr;
protected:

    void changeEvent(QEvent *event);

public:
    void contentDifference(QDir &sDir, QDir &dDir, QFileInfoList &diffList, int dirNum);
    void setExtArray(QLineEdit *inputline, QStringList *arr);
    bool check(QFileInfo info, int folder);
    bool extToCopy(QFileInfo info, QStringList arr);
    int countSize(QLineEdit *inputLine, QButtonGroup *buttons);
    void recursiveContentList(QDir &dir, QFileInfoList &contentList, int dirNum);

signals:
    void newLogLineSignal(QString str);
    void updateProgressBarSignal(int value);

public slots:
    void on_syncBtn_clicked();
    void newLogLineSlot(QString str);
    void updateProgressBarSlot(int value);
    void languageChangeSlot(QString postfix);
};

#endif // MAINWINDOW_H
