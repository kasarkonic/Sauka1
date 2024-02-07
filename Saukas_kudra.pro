QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dyno.cpp \
    global.cpp \
    hwlistsform.cpp \
    hwservice.cpp \
    main.cpp \
    mainwindow.cpp \
    mix.cpp \
    parmani.cpp \
    pipe.cpp \
    pump.cpp \
    sensortablemodel.cpp \
    tvertne.cpp \
    valve.cpp \
    widgetdiagramelement.cpp \
    widgetservice.cpp

HEADERS += \
    dyno.h \
    global.h \
    hwlistsform.h \
    hwservice.h \
    mainwindow.h \
    mix.h \
    parmani.h \
    pipe.h \
    pump.h \
    sensortablemodel.h \
    tvertne.h \
    valve.h \
    widgetdiagramelement.h \
    widgetservice.h

FORMS += \
    hwlistsform.ui \
    hwservice.ui \
    mainwindow.ui \
    parmani.ui \
    widgetservice.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resource.qrc
