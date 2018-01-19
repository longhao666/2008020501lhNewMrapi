#-------------------------------------------------
#
# Project created by QtCreator 2017-12-27T14:10:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = MainWindow
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        widget.cpp

HEADERS += \
        widget.h

FORMS += \
        widget.ui

DESTDIR = ../Bin

TARGET = mrapiLH

INCLUDEPATH += $$PWD/../Bottom
LIBS += -L$$OUT_PWD/../Bin -lBottomLH

INCLUDEPATH += $$PWD/../Move
LIBS += -L$$OUT_PWD/../Bin -lMoveLH

INCLUDEPATH += $$PWD/../SetAndHealth
LIBS += -L$$OUT_PWD/../Bin -lSetAndHealthLH

INCLUDEPATH += $$PWD/../OscilloScope
LIBS += -L$$OUT_PWD/../Bin -lOscilloScopeLH

#INCLUDEPATH += $$PWD/../OscilloScope/qwt/include
#LIBS += -L$$PWD/../OscilloScope/qwt/lib/ -lqwt

INCLUDEPATH += $$PWD/../OscilloScope/qwt/include
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../OscilloScope/qwt/lib/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../OscilloScope/qwt/lib/ -lqwtd
DEPENDPATH += $$PWD/../OscilloScope/qwt/lib

INCLUDEPATH += $$PWD/../Pid
LIBS += -L$$OUT_PWD/../Bin -lPidLH



include(../mr-api.pri)
