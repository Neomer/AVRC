avr-gcc -mmcu=atmega8 -Os -o main.o main.cpp
avr-objcopy -O ihex main.o main.hex
