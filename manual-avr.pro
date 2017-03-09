QT = 

INCLUDEPATH += /usr/lib/avr/include \
	       "C:/Program Files (x86)/Atmel/Studio/7.0/toolchain/avr8/avr8-gnu-toolchain/avr/include"

SOURCES += samples/main.cpp \  
    samples/main_lib.cpp \
    samples/nrf24/nrf24_receiver.cpp \
    samples/nrf24/nrf24_transmitter.cpp \
    samples/pwm/pwm_led.cpp \
    samples/spi/spi_bmp.cpp \
    samples/i2c/i2c_bmp.cpp \
    samples/nrf24/nrf24_2.cpp \
    samples/spi/spi_master.cpp \
    samples/spi/spi_slave.cpp \
    samples/uart/uart.cpp \
    samples/esp8266/esp8266.cpp \
    samples/ir/tsop34338.cpp \
    samples/ir/nec_receiver.cpp \
    samples/ir/nec_sender.cpp \
    samples/pwm/led2.cpp \
    samples/ir/hall.cpp

DEFINES += __AVRC_ARRAY_DONT_CONTROL_RANGE__ \ 
	   __AVRC_INTERRUPTION_ENABLED__ /*\
	   __AVR_ATmega8__ \*/
	   __AVR_ATtiny13__

DISTFILES += \
    samples/compile.sh \
    samples/nrf24/compile_nrf24.sh

HEADERS += \
    include/abstract/Controller.h \
    include/abstract/avr_types.h \
    include/dev/m8/ControllerM8.h \
    include/dev/m8/MemoryM8.h \
    include/abstract/Sensor.h \
    include/sensors/ButtonPullUp.h \
    include/abstract/Object.h \
    include/actors/LED.h \
    include/abstract/Actor.h \
    include/sensors/ButtonHiZ.h \
    include/sensors/Potentiometer.h \
    include/abstract/PWM.h \
    include/dev/m8/PWMM8.h \
    include/dev/m8/UARTM8.h \
    include/abstract/Timer.h \
    include/abstract/Bit.h \
    include/interface/uart.h \
    include/abstract/Queue.h \
    include/connectors/nRF24L01.h \
    include/interface/spi.h \
    include/actors/led_c.h \
    include/sensors/bmp280.h \
    include/interface/i2c.h \
    include/sensors/ds1307.h \
    include/MemMath.h \
    include/core/DateTime.h \
    include/core/BCD.h \
    include/abstract/FIFO.h \
    include/abstract/nec.h

INCLUDEPATH += include
