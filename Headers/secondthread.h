#ifndef SECONDTHREAD_H
#define SECONDTHREAD_H

#include <QObject>
#include <QCoreApplication>
#include "Headers/mainwindow.h"

class secondThread : public QThread
{
public:
    secondThread(QDir _sDir, QDir _dDir, QFileInfoList _diffList, QFileInfoList _diffList1, quint64 _sumSize, mainWnd *_wnd);
    void run();
    QTime *time;
    QDir sDir, dDir;
    QFileInfoList diffList, diffList1;
    mainWnd *wnd;
    QProgressBar *pB;
    quint64 sumSize;
    quint64 curSize = 0;
};

#endif // SECONDTHREAD_H
