clear

rm main.o
rm min_lib.o

echo Compiling simple C code main.cpp
echo

avr-gcc -mmcu=atmega8 -Os -o main.o main.cpp -I ../include
avr-objcopy -O ihex main.o main.hex

echo Compiling AVRC code main_lib.cpp
echo

avr-gcc -mmcu=atmega8 -Os -o main_lib.o main_lib.cpp -I ../include
avr-objcopy -O ihex main_lib.o min_lib.hex

echo 
echo ========================================
echo Simple C code memory usage
echo 
avr-size --mcu=atmega8 --format=avr main.o

echo
echo ========================================
echo AVRC code
echo 

avr-size --mcu=atmega8 --format=avr main_lib.o
echo 
