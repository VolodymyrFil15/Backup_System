#include "testclass.h"


testClass::testClass(QWidget *parent)
    : QWidget(parent)
{
    lay = new QVBoxLayout(this);
    butt = new QPushButton(this);
    lay->addWidget(butt);

}
