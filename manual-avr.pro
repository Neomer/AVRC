QT = 

INCLUDEPATH += /usr/lib/avr/include \
	       "C:/Program Files (x86)/Atmel/Studio/7.0/packs/atmel/ATmega_DFP/1.1.130/include"

SOURCES += main.cpp  

DEFINES += __AVRC_ARRAY_DONT_CONTROL_RANGE__

DISTFILES += \
    compile.sh

HEADERS += \
    abstract/Controller.h \
    abstract/avr_types.h \
    dev/m8/ControllerM8.h \
    dev/m8/MemoryM8.h \
    abstract/Sensor.h \
    sensors/ButtonPullUp.h \
    abstract/Object.h \
    actors/LED.h \
    abstract/Actor.h \
    sensors/ButtonHiZ.h \
    sensors/Potentiometer.h \
    abstract/PWM.h \
    dev/m8/PWMM8.h

