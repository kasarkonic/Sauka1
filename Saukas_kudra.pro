QT  += core gui
QT  += serialport
QT  += gui charts


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    actlistform.cpp \
    acttablemodel.cpp \
    dyno.cpp \
    global.cpp \
    hwservice.cpp \
    main.cpp \
    mainwindow.cpp \
    mix.cpp \
    parmani.cpp \
    pipe.cpp \
    pump.cpp \
    rs232.cpp \
    scale.cpp \
    senslistsform.cpp \
    sensortablemodel.cpp \
    tvertne.cpp \
    valve.cpp \
    widgetdiagramelement.cpp \
    widgetservice.cpp

HEADERS += \
    actlistform.h \
    acttablemodel.h \
    dyno.h \
    global.h \
    hwservice.h \
    mainwindow.h \
    mix.h \
    parmani.h \
    pipe.h \
    pump.h \
    rs232.h \
    scale.h \
    senslistsform.h \
    sensortablemodel.h \
    tvertne.h \
    valve.h \
    widgetdiagramelement.h \
    widgetservice.h

FORMS += \
    actlistform.ui \
    hwservice.ui \
    mainwindow.ui \
    parmani.ui \
    rs232.ui \
    scale.ui \
    senslistsform.ui \
    widgetservice.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resource.qrc
