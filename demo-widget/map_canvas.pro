TEMPLATE = app

CONFIG += c++14 qml_debug console

QT += location

SOURCES += main.cpp \
    PolylineModel.cpp \
    trace.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

HEADERS += \
    PolylineModel.h \
    trace.h

DISTFILES +=
