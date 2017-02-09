#ifndef F_CPU
#define F_CPU 8000000UL
#endif
 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
 
#define ACK 0x7E
 
void spi_init_slave (void)
{
    DDRB=(1<<4);                                  //MISO as OUTPUT
    SPCR=(1<<SPE);                                //Enable SPI
}
 
//Function to send and receive data
unsigned char spi_tranceiver (unsigned char data)
{
    SPDR = data;                                  //Load data into buffer
    while(!(SPSR & (1<<SPIF) ));                  //Wait until transmission complete
    return(SPDR);                                 //Return received data
}
 
int main(void)
{
    spi_init_slave();                             //Initialize slave SPI
    volatile unsigned char data, 
			s = 0,
			pkg = ACK;
    while(1)
    {
        data = spi_tranceiver(pkg);
		if (data == ACK)
		{
			pkg = ACK;
		}
		else
		{
			pkg = data + 1;
		}
        //_delay_ms(20);
    }
}
