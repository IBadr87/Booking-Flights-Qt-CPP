QT       += core gui
QT += network core sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    SeatColor.cpp \
    SeatWidget.cpp \
    bookingflights.cpp \
    continuebooking.cpp \
    customers.cpp \
    flightstatus.cpp \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    SeatColor.h \
    SeatWidget.h \
    bookingflights.h \
    continuebooking.h \
    customers.h \
    flightstatus.h \
    mainwindow.h \

FORMS += \
    SeatWidget.ui \
    bookingflights.ui \
    continuebooking.ui \
    customers.ui \
    flightstatus.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
