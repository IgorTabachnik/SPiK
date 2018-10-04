#-------------------------------------------------
#
# Project created by QtCreator 2018-09-11T16:12:18
#
#-------------------------------------------------
QT       += core gui axcontainer sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RemoteControl_SPiK
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        3rdparty/qextserialport/qextserialport.cpp  \
        3rdparty/libmodbus/src/modbus.c \
        3rdparty/libmodbus/src/modbus-data.c \
        3rdparty/libmodbus/src/modbus-rtu.c \
        3rdparty/libmodbus/src/modbus-tcp.c \
        3rdparty/libmodbus/src/modbus-ascii.c \
        settings.cpp \
        main.cpp \
        mainwindow.cpp \
        usingmodbus.cpp \
        dmodbussettings.cpp \
        enternumberlot.cpp \
        dialog_testnavigo.cpp \
        excelconfig.cpp \
        functiontest.cpp \
        openshorttest.cpp \
    settingsmbdevice.cpp \
    login_BD.cpp \
    ThPollDevices.cpp \
    help_func.cpp \
    testexcel.cpp


HEADERS += \
        3rdparty/qextserialport/qextserialport.h \
        3rdparty/qextserialport/qextserialenumerator.h \
        3rdparty/libmodbus/src/modbus.h \
        settings.h \
        mainwindow.h \
        usingmodbus.h \
        dmodbussettings.h \
        enternumberlot.h \
        dialog_testnavigo.h \
        excelconfig.h \
        functiontest.h \
        openshorttest.h \
    settingsmbdevice.h \
    login_BD.h \
    ThPollDevices.h \
    help_func.h \
    testexcel.h


INCLUDEPATH += 3rdparty/libmodbus \
               3rdparty/libmodbus/src \
               3rdparty/qextserialport \
               src
unix {
    SOURCES += 3rdparty/qextserialport/posix_qextserialport.cpp	\
           3rdparty/qextserialport/qextserialenumerator_unix.cpp
    DEFINES += _TTY_POSIX_
}

win32 {
    SOURCES += 3rdparty/qextserialport/win_qextserialport.cpp \
           3rdparty/qextserialport/qextserialenumerator_win.cpp
    DEFINES += _TTY_WIN_  WINVER=0x0501
    LIBS += -lsetupapi -lws2_32
}

FORMS += \
        mainwindow.ui \
    dmodbussettings.ui \
    enternumberlot.ui \
    dialog_testnavigo.ui \
    settingsmbdevice.ui \
    login_BD.ui \
    testexcel.ui

win32: LIBS += -L$$PWD/'../../../../Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc/' -lvisa32

INCLUDEPATH += $$PWD/'../../../../Program Files (x86)/IVI Foundation/VISA/WinNT/Include'
DEPENDPATH += $$PWD/'../../../../Program Files (x86)/IVI Foundation/VISA/WinNT/Include'
