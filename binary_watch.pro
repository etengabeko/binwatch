TEMPLATE = app
TARGET = bwatch

QT = core  \
     gui

include(common.pro)

HEADERS += \
           bwatch.h

SOURCES += \
           bwatch.cpp  \
           main.cpp

FORMS += bwatch.ui

RESOURCES = led_pic.qrc
