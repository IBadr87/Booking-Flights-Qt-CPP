QT -= gui

QT += sql httpserver

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        deletedata.cpp \
        getdata.cpp \
        main.cpp \
        postdata.cpp \
        updatedata.cpp \
        utils.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    BDD.s3db \
    config.json

HEADERS += \
    deletedata.h \
    getdata.h \
    postdata.h \
    updatedata.h \
    utils.h
