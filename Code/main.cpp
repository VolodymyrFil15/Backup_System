#include "Headers/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QTime *time;
    QApplication a(argc, argv);
    mainWnd w("ru");
    w.show();
    w.thirdTab->logHolder->append(time->currentTime().toString("h:m:s") + QApplication::tr(": Program started"));
    w.copyingSettingsTab->firstSGB->minSizeCB->setText(QApplication::tr("Syncronize"));
    return a.exec();
}
