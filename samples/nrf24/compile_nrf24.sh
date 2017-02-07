clear

echo Compiling NRF24 Receiver code...
echo

avr-gcc -mmcu=atmega8 -Os -o nrf24_receiver.o nrf24_receiver.cpp -I ../../include
avr-objcopy -O ihex nrf24_receiver.o nrf24_receiver.hex

echo Compiling NRF24 Transmitter code...
echo

avr-gcc -mmcu=atmega8 -Os -o nrf24_transmitter.o nrf24_transmitter.cpp -I ../../include
avr-objcopy -O ihex nrf24_transmitter.o nrf24_transmitter.hex

echo 
echo ========================================
echo NRF24 Receiver code memory usage
echo 
avr-size --mcu=atmega8 --format=avr nrf24_receiver.o

echo
echo ========================================
echo NRF24 Transmitter code memory usage
echo 

avr-size --mcu=atmega8 --format=avr nrf24_transmitter.o
echo 
