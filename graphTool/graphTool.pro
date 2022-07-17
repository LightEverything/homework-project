QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authorwidget.cpp \
    coffeewidget.cpp \
    helperwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    nodegraphscene.cpp \
    nodeitem.cpp \
    settingwidget.cpp

HEADERS += \
    authorwidget.h \
    coffeewidget.h \
    helperwidget.h \
    mainwindow.h \
    nodegraphscene.h \
    nodeitem.h \
    sceneMode.h \
    settingwidget.h

FORMS += \
    authorwidget.ui \
    coffeewidget.ui \
    helperwidget.ui \
    mainwindow.ui \
    settingwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    coffee.qrc
