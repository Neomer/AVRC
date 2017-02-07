#define F_CPU	8000000UL

#include <avr/io.h>
#include <avr/iom8.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include <MemMath.h>
#include <abstract/uart.h>
#include <actors/led_c.h>

#define  SPI_PORT			PORTB
#define  SPI_DDR			DDRB
#define  SPI_MOSI			3
#define  SPI_SCK			5
#define  SPI_SS				2
#define  SPI_MISO			4

#define SPI_CE				0
#define SPI_PIN_CE			PINC
#define SPI_PORT_CE			PORTC
#define SPI_DDR_CE			DDRC

#define SPI_IRQ				1
#define SPI_PIN_IRQ			PINC
#define SPI_PORT_IRQ		PORTC
#define SPI_DDR_IRQ			DDRC

#include <connectors/nRF24L01.h>

int main()
{
	led(DDRB, 0);
	
	uart_init(UART_BAUD_8MHz_38400);
	nrf24_init();
	nrf24_config(sizeof(uint8_t), 2);
	
	uint8_t b;
	
	__setLow(DDRC, 5);
	__setLow(PORTC, 5);
	
	while (1)
	{
		if (__bitIsHigh(PINC, 5))
		{
			led_turn_on(PORTB, 0);
		}
		else
		{
			led_turn_off(PORTB, 0);
		}
		_delay_ms(500);
		
	}
}
