QT += widgets
QT += xml

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

SOURCES += \
    main.cpp \
    automate.cpp \
    autocell.cpp \
    Xml_Dom.cpp

HEADERS += \
    automate.h \
    autocell.h \
    Xml_Dom.h
