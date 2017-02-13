#ifndef F_CPU
#define F_CPU 8000000UL
#endif
 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <interface/uart.h>

#include <stdlib.h>
#include <string.h>

#define ACK 0x7E

//Initialize SPI Master Device
void spi_init_master (void)
{
	DDRB = (1<<5)|(1<<3)|(1<<2);           //Set MOSI, SCK as Output
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0); //Enable SPI, Set as Master
                                       //Prescaler: Fosc/16, Enable Interrupts
}
 
//Function to send and receive data
unsigned char spi_tranceiver (unsigned char data)
{

    SPDR = data;                       //Load data into the buffer
    while(!(SPSR & (1<<SPIF) ));       //Wait until transmission complete
	PORTB &= ~(1 << 2);
	return(SPDR);                      //Return received data
}
 
//Main
int main(void)
{
	uart_init(UART_BAUD_8MHz_9600);
    spi_init_master();                  //Initialize SPI Master
 
    unsigned char data;                 //Received data stored here
    uint8_t x = 0;                      //Counter value which is sent
 
    while(1)
    {
//		uart_send_str("x=");
//		uart_send_int(x);
//		uart_send_str(" ");
		PORTB &= ~(1 << 2);
        data = spi_tranceiver(x);
		uart_send_int(data);
        if(data == ACK)
		{
	        x = spi_tranceiver(ACK);
			uart_send_str(" OK.. x=");
			uart_send_int(x);
			uart_send_char('\n');
        }
        else 
		{
			uart_send_str("FAILED\n");
        }
		PORTB |= (1 << 2);
        _delay_ms(500);                 //Wait
    }
}
