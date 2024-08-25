QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Processor.cpp \
    ScoreWindow.cpp \
    Team.cpp \
    main.cpp \
    MainWindow.cpp

HEADERS += \
    MainWindow.h \
    Processor.h \
    ScoreWindow.h \
    Team.h

FORMS += \
    mainwindow.ui \
    scorewindow.ui

RESOURCES += \
    resources.qrc

# Needed for setting icon in executable
ICON = ICANT_KEKW.ico
RC_FILE = MarioKartLounge.rc


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    MarioKartLounge.rc

