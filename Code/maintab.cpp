#include "Headers/maintab.h"
#include "Headers/mainwindow.h"

mainTab::mainTab(mainWnd *_par, QWidget *parent) : QWidget(parent)
{
    par = _par;
    lay = new QGridLayout(this);

    lb1 = new QLabel("Folder 1", this);
    lb2 = new QLabel("Folder 2", this);

    lvFirst = new QListView(this);
    lvSecond = new QListView(this);

    levelUp1 = new QPushButton("Level Up", this);
    levelUp2 = new QPushButton("Level Up", this);

    lay->addWidget(lb1, 1, 1);
    lay->addWidget(lb2, 1, 2);

    lay->addWidget(lvFirst, 2, 1);
    lay->addWidget(lvSecond, 2, 2);

    lay->addWidget(levelUp1, 3, 1);
    lay->addWidget(levelUp2, 3, 2);

    model = new QFileSystemModel(this);
    model->setFilter(QDir::AllEntries);
    model->setRootPath("");;
    lvFirst->setModel(model);
    lvSecond->setModel(model);
    connect(lvFirst, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(on_lvFirst_doubleClicked(QModelIndex)));
    connect(lvSecond, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(on_lvFirst_doubleClicked(QModelIndex)));
}

void mainTab::on_lvFirst_doubleClicked(const QModelIndex &index)
{
    QListView* listView = (QListView*)sender();
    QFileInfo fileinfo = model->fileInfo(index);
    if (fileinfo.fileName() == "..")
    {
        QDir dir = fileinfo.dir();
        dir.cdUp();
        listView->setRootIndex(model->index(dir.absolutePath()));
    }
    else if (fileinfo.fileName() == ".")
    {
        listView->setRootIndex(model->index(""));
    }
    else if (fileinfo.isDir())
    {
        listView->setRootIndex(index);
    }
    else if (par->fileOpenBool)
    {
        QDesktopServices::openUrl(fileinfo.absoluteFilePath());
    }
}
