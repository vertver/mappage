QT       += core gui widgets
QT += quick
TARGET = demo-widget
TEMPLATE = app

include(../qtimgui.pri)

SOURCES += \
    demo-widget.cpp

DISTFILES += \
    ../main.qml
