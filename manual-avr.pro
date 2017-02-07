QT = 

INCLUDEPATH += /usr/lib/avr/include \
	       "C:/Program Files (x86)/Atmel/Studio/7.0/toolchain/avr8/avr8-gnu-toolchain/avr/include"

SOURCES += samples/main.cpp \  
    samples/main_lib.cpp \
    samples/nrf24/nrf24_receiver.cpp \
    samples/nrf24/nrf24_transmitter.cpp

DEFINES += __AVRC_ARRAY_DONT_CONTROL_RANGE__ \ 
	   __AVRC_INTERRUPTION_ENABLED__ \
	   __AVR_ATmega8__

DISTFILES += \
    samples/compile.sh \
    samples/nrf24/compile_nrf24.sh

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
    abstract/spi.h \
    actors/led_c.h

INCLUDEPATH += ../
