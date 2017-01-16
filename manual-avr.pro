QT = 

INCLUDEPATH += /usr/lib/avr/include

SOURCES += main.cpp 

#DEFINES += __AVR_ATmega8__

DISTFILES += \
    compile.sh

HEADERS += \
    Controller.h \
    avr_types.h \
    dev/m8/ControllerM8.h \
    dev/m8/MemoryM8.h

