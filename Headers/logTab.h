#ifndef LOG_H
#define LOG_H

#include <QObject>
#include <QWidget>
#include <QTextBrowser>
#include <QGridLayout>

class logTab : public QWidget
{
    Q_OBJECT
public:
    explicit logTab(QWidget *parent = 0);

public:
    QTextBrowser *logHolder;
    QGridLayout *lay;

signals:

public slots:
};

#endif // LOG_H
