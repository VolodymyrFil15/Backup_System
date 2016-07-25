#include "Headers/mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    globalLayout = new QGridLayout(this);

    syncBtn = new QPushButton("Sync", this);
    tabs = new QTabWidget(this);

    mainTab *firstTab = new mainTab;
    settingsTab *secondTab = new settingsTab;
    logTab *thirdTab = new logTab;

    tabs->addTab(firstTab, "Main");
    tabs->addTab(secondTab, "Settings");
    tabs->addTab(thirdTab, "Log");
    thirdTab->logHolder->append(time->currentTime().toString("h:m:s") + ": Program started");
    globalLayout->addWidget (tabs, 1, 1);
    globalLayout->addWidget(syncBtn, 2, 1);

    progressBar = new QProgressBar();
    progressBar->setValue(0);
    globalLayout->addWidget(progressBar, 3, 1);
}

MainWindow::~MainWindow()
{

}



int MainWindow::countSize(QLineEdit *inputLine, QButtonGroup *buttons)
{
    if (inputLine->text() != NULL)
    {
            if (buttons->checkedId() == -2)
            {
                return inputLine->text().toULongLong();
            }
            else if (buttons->checkedId() == -3)
            {
                return inputLine->text().toULongLong() * 1024;
            }
            else if (buttons->checkedId() == -4)
            {
                return inputLine->text().toULongLong() * 1048576;
            } else {
                QMessageBox::information(NULL,QObject::tr("Error"), tr("Ви не вибрали одиницю виміру"));
                return -1;
            }
        } else {
        QMessageBox::information(NULL,QObject::tr("Error"), tr("Ви не ввели розмір"));
        return -1;
    }
    return -1;
}
