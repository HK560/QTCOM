QT       += core gui
QT += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/mmessagebox.cpp \
    src/ListenPortThread.cpp \
    src/com.cpp \
    src/comportinfo.cpp \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS += \
    include/ListenPortThread.h \
    include/com.h \
    include/mainwindow.h \
    include/comportinfo.h \
    include/mmessagebox.h
    
INCLUDEPATH += \include

TRANSLATIONS += ress/language_zh.ts \
                ress/language_en.ts


FORMS += \
    forms/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ress/res.qrc

DISTFILES += \
    ress/language_en.qm \
    ress/style.qss
