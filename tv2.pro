
CONFIG += qt

DEFINES += QT57

QT += core widgets

HEADERS += TreeMainWindow.h
HEADERS += TreeWidget.h
HEADERS += TextEdit.h

SOURCES += TreeAppli.cpp
SOURCES += TreeMainWindow.cpp
SOURCES += TreeWidget.cpp
SOURCES += TextEdit.cpp

msvc:RC_FILE += tv2.rc
msvc:QMAKE_RC = rc -D_MSC_VER

TARGET = tv2
