QT  += core gui
QT  += serialport
QT  += gui charts
QT += serialbus


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
    hwports.cpp \
    hwservice.cpp \
    main.cpp \
    mainwindow.cpp \
    mix.cpp \
    modbusserver.cpp \
    parmani.cpp \
    pipe.cpp \
    procui1.cpp \
    procui2.cpp \
    pump.cpp \
    rs232.cpp \
    scale.cpp \
    scalesbase.cpp \
    scalesmass.cpp \
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
    hwports.h \
    hwservice.h \
    mainwindow.h \
    mix.h \
    modbusserver.h \
    parmani.h \
    pipe.h \
    procui1.h \
    procui2.h \
    pump.h \
    rs232.h \
    scale.h \
    scalesbase.h \
    scalesmass.h \
    senslistsform.h \
    sensortablemodel.h \
    tvertne.h \
    valve.h \
    widgetdiagramelement.h \
    widgetservice.h

FORMS += \
    actlistform.ui \
    hwports.ui \
    hwservice.ui \
    mainwindow.ui \
    parmani.ui \
    procui1.ui \
    procui2.ui \
    rs232.ui \
    scale.ui \
    scalesbase.ui \
    scalesmass.ui \
    senslistsform.ui \
    widgetservice.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    resource.qrc
