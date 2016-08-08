#-------------------------------------------------
#
# Project created by QtCreator 2016-07-06T20:35:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Backup_system

TEMPLATE = app

SOURCES += Code/main.cpp\
    Code/mainwindow.cpp \
    Code/maintab.cpp \
    Code/settingstab.cpp \
    Code/logTab.cpp \
    Code/settingsgroupbox.cpp \
    Code/secondthread.cpp \
    Code/programsettings.cpp

HEADERS  += Headers/mainwindow.h \
    Headers/maintab.h \
    Headers/settingstab.h \
    Headers/settingsGroupBox.h \
    Headers/logTab.h \
    Headers/secondthread.h \
    Headers/programsettings.h

TRANSLATIONS += Translations/backup_system_ru.ts\
    Translations/backup_system_uk.ts

DISTFILES += \
    Translations/Backup_system_uk.qm \
    Translations/Backup_system_ru.ts \
    Translations/Backup_system_uk.ts

