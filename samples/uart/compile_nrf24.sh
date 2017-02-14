clear

rm firmware.o
rm firmware.hex

echo Compiling...
avr-gcc -mmcu=atmega8 -Os -o firmware.o uart.cpp -I ../../include
avr-objcopy -O ihex firmware.o firmware.hex

avr-size --mcu=atmega8 --format=avr firmware.o

echo Write to IC
avrdude -U flash:w:firmware.hex -p m8 -b 9600 -c usbasp -e

