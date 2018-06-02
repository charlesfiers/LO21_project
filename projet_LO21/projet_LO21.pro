QT += \
    widgets \
    xml


QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

SOURCES += \
    main.cpp \
    xmldoc.cpp

HEADERS += \
    xmldoc.h

DISTFILES +=

OTHER_FILES += \
    doc1.xml
