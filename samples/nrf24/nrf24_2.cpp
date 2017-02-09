#define F_CPU	8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include <MemMath.h>
#include <abstract/uart.h>
#include <actors/led_c.h>

#define  SPI_PORT			PORTB
#define  SPI_DDR			DDRB
#define  SPI_SS				2
#define  SPI_MOSI			3
#define  SPI_MISO			4
#define  SPI_SCK			5

#define SPI_CE				4
#define SPI_PIN_CE			PINC
#define SPI_PORT_CE			PORTC
#define SPI_DDR_CE			DDRC

#define SPI_IRQ				5
#define SPI_PIN_IRQ			PINC
#define SPI_PORT_IRQ		PORTC
#define SPI_DDR_IRQ			DDRC
#define NRF24_IRQ_INT		INT0_vect


// Переводит порт в режим чтения/записи
#define spi_ss_low			__setLow(SPI_PORT, SPI_SS)
#define spi_ss_high			__setHigh(SPI_PORT, SPI_SS)
#define spi_wait_status		__waitHigh(SPSR, SPIF);


void spi_init_master( void )
{
	DDRB = (1<<5)|(1<<3)|(1<<2);
    SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

volatile uint8_t spi_fast_exchage( uint8_t data )
{
	SPDR = data;
	spi_wait_status;
	return SPDR;
}

#define NRF24_R_REGISTER                      0x00 //читаем регистр
#define NRF24_W_REGISTER                      0x20 //пишем в регистр
#define NRF24_REGISTER_MASK					  0x1F

int main()
{
	uart_init(UART_BAUD_8MHz_9600);
	spi_init_master();
	
	__setLow(DDRD, 7);
	__setHigh(PORTD, 7);
	
	volatile uint8_t b;
	volatile bool fl;
	volatile bool wcol;
	volatile uint8_t spsr;
	while (1)
	{
		if (__bitIsLow(PIND, 7))
		{
			uart_send_str("status: ");
			spi_ss_low;
			SPDR = 0xff;
			fl = true;
			while(fl)
			{
				spsr = SPSR;
				fl = ((spsr & (1<<SPIF)) | (spsr & (1 << WCOL))) == 0;
				wcol = (spsr & (1 << WCOL)) != 0;
			}
			if (wcol)
				uart_send_str("writing collision!");
			b = SPDR;
			spi_ss_high;
			uart_send_int( b );

			uart_send_str(" cfg: ");
			spi_ss_low;
			SPDR = (NRF24_R_REGISTER | (0x00 & NRF24_REGISTER_MASK));
			fl = true;
			while(fl)
			{
				spsr = SPSR;
				fl = ((spsr & (1<<SPIF)) | (spsr & (1 << WCOL))) == 0;
				wcol = (spsr & (1 << WCOL)) != 0;
			}
			if (wcol)
				uart_send_str("writing collision!");
			b = SPDR;
			spi_ss_high;
			uart_send_int( b );
			
			uart_send_str(" rf: ");
			spi_ss_low;
			SPDR = (NRF24_R_REGISTER | (0x05 & NRF24_REGISTER_MASK));
			fl = true;
			while(fl)
			{
				spsr = SPSR;
				fl = ((spsr & (1<<SPIF)) | (spsr & (1 << WCOL))) == 0;
				wcol = (spsr & (1 << WCOL)) != 0;
			}
			if (wcol)
				uart_send_str("writing collision!");
			b = SPDR;
			_delay_ms(10);
			spi_ss_high;
			uart_send_int( b );
			uart_send_char('\n');
//			uart_send_char('#');
			
			_delay_ms(3000);
		}
	}
}

