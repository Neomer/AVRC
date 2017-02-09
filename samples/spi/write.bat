cls

rm %FILE%.o
rm %FILE%.hex

set FILE=%1
avr-gcc -mmcu=atmega8 -Os -o %FILE%.o %FILE%.cpp -I ../../include
avr-objcopy -O ihex %FILE%.o %FILE%.hex

C:\WinAVR-20100110\bin\avrdude.exe  -U flash:w:%FILE%.hex -p m8 -b 9600 -c usbasp -e
pause