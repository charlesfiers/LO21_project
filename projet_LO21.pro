QT += widgets
QT += xml

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

SOURCES += \
    main.cpp \
    automate.cpp \
    Xml_Dom.cpp \
    mainwindow.cpp \
    autocelldim1.cpp \
    autocelldim2.cpp

HEADERS += \
    automate.h \
    Xml_Dom.h \
    mainwindow.h \
    autocelldim1.h \
    autocelldim2.h
