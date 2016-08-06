#include "Headers/mainwindow.h"

mainWnd::mainWnd(QWidget *parent)
    : QWidget(parent)
{
    globalLayout = new QGridLayout(this);

    syncBtn = new QPushButton("Sync", this);
    tabs = new QTabWidget(this);

    firstTab = new mainTab(this);
    secondTab = new settingsTab(this);
    thirdTab = new logTab;

    tabs->addTab(firstTab, "Main");
    tabs->addTab(secondTab, "Settings");
    tabs->addTab(thirdTab, "Log");

    thirdTab->logHolder->append(time->currentTime().toString("h:m:s") + ": Program started");

    globalLayout->addWidget (tabs, 1, 1);
    globalLayout->addWidget(syncBtn, 2, 1);

    progressBar = new QProgressBar();
    progressBar->setValue(0);
    globalLayout->addWidget(progressBar, 3, 1);

    connect(this, SIGNAL(newLogLineSignal(QString)), this, SLOT(newLogLineSlot(QString)));
    connect(this, SIGNAL(updateProgressBarSignal(int)), this, SLOT(updateProgressBarSlot(int)));
    connect(syncBtn, SIGNAL(clicked()), this, SLOT(on_syncBtn_clicked()));
}

bool mainWnd::extToCopy(QFileInfo info, QStringList arr)
{
    for (int i = 0; i < arr.length(); i++)
    {
        if (info.fileName().endsWith(arr[i]))
        {
            return true;
        }
    }
    return false;
}

bool mainWnd::check(QFileInfo info, int folder)
{
    if (info.isDir())
    {
        if ((folder == 1) && !(this->secondTab->firstSGB->foldersBool))
        {
            return false;
        }
        else if ((folder == 2) && !(this->secondTab->secondSGB->foldersBool))
        {
            return false;
        } else return true;
    }
    if (info.isFile())
    {
        if ((folder == 1) && !(this->secondTab->firstSGB->filesBool))
        {
            return false;
        }
        else if ((folder == 2) && !(this->secondTab->secondSGB->filesBool))
        {
            return false;
        }
    }
    if (folder == 1 && this->secondTab->firstSGB->minSizeBool)
    {
        if (info.size() < minFrom1Int)
        {
            return false;
        }
    }
    if (folder == 1 && this->secondTab->firstSGB->maxSizeBool)
    {
        if (info.size() > maxFrom1Int)
        {
            return false;
        }
    }
    if (folder == 2 && this->secondTab->secondSGB->minSizeBool)
    {
        if (info.size() < minFrom2Int)
        {
            return false;
        }
    }
    if (folder == 2 && this->secondTab->secondSGB->maxSizeBool)
    {
        if (info.size() > maxFrom2Int)
        {
            return false;
        }
    }
    if (folder == 1 && this->secondTab->firstSGB->extToCopyBool)
    {
        return extToCopy(info, extensionsFrom1);
    }
    if (folder == 2 && this->secondTab->firstSGB->extToCopyBool)
    {
        return extToCopy(info, extensionsFrom2);
    }
    return true;
}

void mainWnd::setExtArray(QLineEdit *inputline, QStringList *arr)
{
    if (inputline->text() != NULL)
    {
        foreach (QString ext, inputline->text().split(","))
        {
            arr->append(ext.remove(" ").remove("*"));
        }
    }
    else
    {
        QMessageBox::information(NULL, QObject::tr("Помилка"), tr("Ви не ввели розширення"));
        return;
    }
}


void mainWnd::recursiveContentList(QDir &dir, QFileInfoList &contentList, int dirNum)
{
    this->thirdTab->logHolder->append(time->currentTime().toString("h:m:s") + ": Заносимо в масив елементи для копіювання з папки: " + QString(dir.absolutePath()));
    foreach(QFileInfo info, dir.entryInfoList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot,QDir::Name|QDir::DirsFirst))
    {
        if (check(info, dirNum))
        {
            contentList.append(info);
            sumSize += info.size();
            if(info.isDir() && dir.cd(info.fileName()))
            {
                recursiveContentList(dir, contentList, dirNum);
                dir.cdUp();
            }
        }
    }
}

int mainWnd::countSize(QLineEdit *inputLine, QButtonGroup *buttons)
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

void mainWnd::contentDifference(QDir &sDir, QDir &dDir, QFileInfoList &diffList, int dirNum)
{
    if (dirNum == 1)
    {
        this->thirdTab->logHolder->append(time->currentTime().toString("h:m:s") + ": Заносимо в масив елементи для копіювання з папки 1");
    }
    else
    {
        this->thirdTab->logHolder->append(time->currentTime().toString("h:m:s") + ": Заносимо в масив елементи для копіювання з папки 2");
    }

    foreach(QFileInfo sInfo, sDir.entryInfoList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot,QDir::Name|QDir::DirsFirst))
    {
        bool fileExists = false;
        foreach(QFileInfo dInfo, dDir.entryInfoList(QDir::Files|QDir::Dirs|QDir::NoDotAndDotDot,QDir::Name|QDir::DirsFirst))
        {
            if(sInfo.fileName() == dInfo.fileName())
            {
                fileExists = true;
                if (sInfo.isDir() && check(sInfo, dirNum))
                {
                    sDir.cd(sInfo.fileName());
                    dDir.cd(sInfo.fileName());
                    contentDifference(sDir, dDir, diffList, dirNum);
                    sDir.cdUp();
                    dDir.cdUp();
                    break;
                }
            }
        }
        if (!fileExists && check(sInfo, dirNum))
        {
            diffList.append(sInfo);
            sumSize += sInfo.size();
            if (sInfo.isFile())
                continue;
            else
            {
                sDir.cd(sInfo.fileName());
                recursiveContentList(sDir, diffList, dirNum);
                sDir.cdUp();
            }
        }
    }
}

void mainWnd::on_syncBtn_clicked()
{
    if (secondTab->firstSGB->extToCopyBool)
    {
        setExtArray(secondTab->firstSGB->extensionsLE, &extensionsFrom1);
        if(extensionsFrom1.length() == 0) return;
    }
    if (secondTab->secondSGB->extToCopyBool)
    {
        setExtArray(secondTab->secondSGB->extensionsLE, &extensionsFrom2);
        if(extensionsFrom2.length() == 0) return;
    }
    if(secondTab->firstSGB->minSizeBool)
    {
        minFrom1Int = countSize(secondTab->firstSGB->minSizeLE, secondTab->firstSGB->minSizeBG);
        if(minFrom1Int < 0) return;
    }
    if(secondTab->secondSGB->minSizeBool)
    {
        minFrom2Int = countSize(secondTab->secondSGB->minSizeLE, secondTab->secondSGB->minSizeBG);
        if(minFrom2Int < 0) return;
    }
    if(secondTab->firstSGB->maxSizeBool)
    {
        maxFrom1Int = countSize(secondTab->firstSGB->maxSizeLE, secondTab->firstSGB->maxSizeBG);
        if(maxFrom1Int < 0) return;
    }
    if(secondTab->secondSGB->maxSizeBool)
    {
        maxFrom2Int = countSize(secondTab->secondSGB->maxSizeLE, secondTab->secondSGB->maxSizeBG);
        if(maxFrom2Int < 0) return;

    }
    this->progressBar->setValue(0);
    QDir sDir = QDir(this->firstTab->model->filePath(this->firstTab->lvFirst->rootIndex()));
    QDir dDir = QDir(this->firstTab->model->filePath(this->firstTab->lvSecond->rootIndex()));
    QDir curDir = QDir::currentPath();
    QFileInfoList diffList = QFileInfoList();
    QFileInfoList diffList1 = QFileInfoList();
    if (sDir != curDir && dDir != curDir)
    {
        if (sDir != dDir)
        {
            sumSize = 0;
            contentDifference(sDir, dDir, diffList, 1);
            contentDifference(dDir, sDir, diffList1, 2);
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(NULL, "Підтвердження", "Провести копіювання із заданими параметрами?", QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes){
                this->thirdTab->logHolder->append("Загальний об'єм файлів для копіювання " + QString::number(sumSize) + " байт.");
                rthr = new secondThread(sDir, dDir, diffList, diffList1, sumSize, this);
                rthr->start();
            }
        }
        else
        {
            QMessageBox::information(NULL,QObject::tr("Помилка"), tr("Ви вибрали одну папку двічі"));
        }
    }
    else
    {
        QMessageBox::information(NULL,QObject::tr("Помилка"), tr("Ви не вибрали шлях до однієї з папок"));
    }
}

void mainWnd::newLogLineSlot(QString str)
{
    thirdTab->logHolder->append(str);
}

void mainWnd::updateProgressBarSlot(int value)
{
    progressBar->setValue(value);
}


mainWnd::~mainWnd()
{

}
