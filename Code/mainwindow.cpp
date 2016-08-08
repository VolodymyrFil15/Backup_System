#include "Headers/mainwindow.h"

mainWnd::mainWnd(QWidget *parent) : QWidget(parent)
{
    version = "v0.1 beta";
    translator = new QTranslator(this);
    QApplication::installTranslator(translator);
    this->setWindowTitle(tr("Backup system ") + version);
    globalLayout = new QGridLayout(this);

    syncBtn = new QPushButton(tr("Syncronize"), this);
    tabs = new QTabWidget(this);

    firstTab = new mainTab(this);
    copyingSettingsTab = new copyingSettings(this);
    thirdTab = new logTab;
    programSettingsTab = new programSettings(this);

    tabs->addTab(firstTab, tr("Main"));
    tabs->addTab(copyingSettingsTab, tr("Copying Settings"));
    tabs->addTab(thirdTab, tr("Log"));
    tabs->addTab(programSettingsTab, tr("Program settings"));

    thirdTab->logHolder->append(time->currentTime().toString("h:m:s") + tr(": Program started"));

    globalLayout->addWidget (tabs, 1, 1);
    globalLayout->addWidget(syncBtn, 2, 1);
    progressBar = new QProgressBar();
    progressBar->setValue(0);
    globalLayout->addWidget(progressBar, 3, 1);

    connect(this, SIGNAL(newLogLineSignal(QString)), this, SLOT(newLogLineSlot(QString)));
    connect(this, SIGNAL(updateProgressBarSignal(int)), this, SLOT(updateProgressBarSlot(int)));
    connect(syncBtn, SIGNAL(clicked()), this, SLOT(on_syncBtn_clicked()));
    connect(programSettingsTab, SIGNAL(languageChangeSignal(QString)), this,
            SLOT(languageChangeSlot(QString)));
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
        if ((folder == 1) && !(this->copyingSettingsTab->firstSGB->foldersBool))
        {
            return false;
        }
        else if ((folder == 2) && !(this->copyingSettingsTab->secondSGB->foldersBool))
        {
            return false;
        } else return true;
    }
    if (info.isFile())
    {
        if ((folder == 1) && !(this->copyingSettingsTab->firstSGB->filesBool))
        {
            return false;
        }
        else if ((folder == 2) && !(this->copyingSettingsTab->secondSGB->filesBool))
        {
            return false;
        }
    }
    if (folder == 1 && this->copyingSettingsTab->firstSGB->minSizeBool)
    {
        if (info.size() < minFrom1Int)
        {
            return false;
        }
    }
    if (folder == 1 && this->copyingSettingsTab->firstSGB->maxSizeBool)
    {
        if (info.size() > maxFrom1Int)
        {
            return false;
        }
    }
    if (folder == 2 && this->copyingSettingsTab->secondSGB->minSizeBool)
    {
        if (info.size() < minFrom2Int)
        {
            return false;
        }
    }
    if (folder == 2 && this->copyingSettingsTab->secondSGB->maxSizeBool)
    {
        if (info.size() > maxFrom2Int)
        {
            return false;
        }
    }
    if (folder == 1 && this->copyingSettingsTab->firstSGB->extToCopyBool)
    {
        return extToCopy(info, extensionsFrom1);
    }
    if (folder == 2 && this->copyingSettingsTab->firstSGB->extToCopyBool)
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
        QMessageBox::warning(NULL, QObject::tr("Error!"), tr("You haven't inserted file's extensions"));
        return;
    }
}


void mainWnd::recursiveContentList(QDir &dir, QFileInfoList &contentList, int dirNum)
{
    this->thirdTab->logHolder->append(time->currentTime().toString("h:m:s") + tr(": Finding files to copy from folder: ") + QString(dir.absolutePath()));
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
            inputLine->setFocus();
            QMessageBox::warning(NULL,QObject::tr("Error!"), tr("You haven't chosen size unit"));
            return -1;
        }
    } else {
        inputLine->setFocus();
        QMessageBox::warning(NULL,QObject::tr("Error!"), tr("You haven't inserted size"));
        return -1;
    }
    return -1;
}

void mainWnd::contentDifference(QDir &sDir, QDir &dDir, QFileInfoList &diffList, int dirNum)
{
    if (dirNum == 1)
    {
        this->thirdTab->logHolder->append(time->currentTime().toString("h:m:s") + tr(": Finding files to copy from folder 1"));
    }
    else
    {
        this->thirdTab->logHolder->append(time->currentTime().toString("h:m:s") + tr(": Finding files to copy from folder 2"));
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
    if (copyingSettingsTab->firstSGB->extToCopyBool)
    {
        setExtArray(copyingSettingsTab->firstSGB->extensionsLE, &extensionsFrom1);
        if(extensionsFrom1.length() == 0) return;
    }
    if (copyingSettingsTab->secondSGB->extToCopyBool)
    {
        setExtArray(copyingSettingsTab->secondSGB->extensionsLE, &extensionsFrom2);
        if(extensionsFrom2.length() == 0) return;
    }
    if(copyingSettingsTab->firstSGB->minSizeBool)
    {
        minFrom1Int = countSize(copyingSettingsTab->firstSGB->minSizeLE, copyingSettingsTab->firstSGB->minSizeBG);
        if(minFrom1Int < 0) return;
    }
    if(copyingSettingsTab->secondSGB->minSizeBool)
    {
        minFrom2Int = countSize(copyingSettingsTab->secondSGB->minSizeLE, copyingSettingsTab->secondSGB->minSizeBG);
        if(minFrom2Int < 0) return;
    }
    if(copyingSettingsTab->firstSGB->maxSizeBool)
    {
        maxFrom1Int = countSize(copyingSettingsTab->firstSGB->maxSizeLE, copyingSettingsTab->firstSGB->maxSizeBG);
        if(maxFrom1Int < 0) return;
    }
    if(copyingSettingsTab->secondSGB->maxSizeBool)
    {
        maxFrom2Int = countSize(copyingSettingsTab->secondSGB->maxSizeLE, copyingSettingsTab->secondSGB->maxSizeBG);
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
            reply = QMessageBox::question(NULL, tr("Confirmation"), tr("Perform copying with given parameters?"), QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes){
                this->thirdTab->logHolder->append(tr("Total size of files to copy ") + QString::number(sumSize) + tr(" bytes."));
                rthr = new secondThread(sDir, dDir, diffList, diffList1, sumSize, this);
                rthr->start();
            }
        }
        else
        {
            QMessageBox::warning(NULL,QObject::tr("Error!"), tr("You have chosen same folder twice"));
        }
    }
    else
    {
        QMessageBox::warning(NULL,QObject::tr("Error!"), tr("You haven't chosen one of folders"));
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

void mainWnd::languageChangeSlot(QString postfix)
{
    QApplication::removeTranslator(translator);
    translator = new QTranslator(this);
    translator->load("translations/" + QApplication::applicationName() + "_" + postfix);
    QApplication::installTranslator(translator);
}



mainWnd::~mainWnd()
{

}

void mainWnd::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange){
        programSettingsTab->closeCheckBox->setText(tr(syncBtn->text().toStdString().c_str()));
        syncBtn->setText(tr(syncBtn->text().toStdString().c_str()));
        tabs->setTabText(tabs->indexOf(firstTab), tr("Main"));
        tabs->setTabText(tabs->indexOf(copyingSettingsTab), tr("Copying Settings"));
        tabs->setTabText(tabs->indexOf(thirdTab), tr("Log"));
        tabs->setTabText(tabs->indexOf(programSettingsTab), tr("Program settings"));
        QList<QCheckBox *> list = this->findChildren<QCheckBox *>();
        foreach(QCheckBox * ch, list)
        {
            ch->setText(tr(ch->text().toStdString().c_str()));
            QMessageBox::information(this, " ", tr(ch->text().toStdString().c_str()));
        }
    }
    else
    {
        QWidget::changeEvent(event);
    }
}
