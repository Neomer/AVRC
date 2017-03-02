cls

del firmware.o
del firmware.hex

set FILE=%1
avr-gcc -mmcu=atmega8 -Os -o firmware.o %FILE%.cpp -I ../../include
avr-objcopy -O ihex firmware.o firmware.hex

C:\WinAVR-20100110\bin\avrdude.exe  -U flash:w:firmware.hex -p m8 -b 9600 -c usbasp -e