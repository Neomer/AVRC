QT = 

INCLUDEPATH += /usr/lib/avr/include \
	       "C:/Program Files (x86)/Atmel/Studio/7.0/toolchain/avr8/avr8-gnu-toolchain/avr/include"

SOURCES += main.cpp \  
    main_lib.cpp \
    nrf24_receiver.cpp \
    nrf24_transmitter.cpp

DEFINES += __AVRC_ARRAY_DONT_CONTROL_RANGE__ \ 
	   __AVRC_INTERRUPTION_ENABLED__ \
	   __AVR_ATmega8__

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
    dev/m8/PWMM8.h \
    dev/m8/UARTM8.h \
    abstract/Timer.h \
    abstract/Bit.h \
    abstract/uart.h \
    abstract/Queue.h \
    connectors/nRF24L01.h \
    abstract/spi.h

