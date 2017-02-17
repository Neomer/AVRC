#define F_CPU	8000000UL

#include <avr/io.h>
#include <avr/iom8.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

#include <MemMath.h>
#include <interface/uart.h>
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

//#define AVRC_INTERRUPT
#include <connectors/nRF24L01.h>

int main()
{
	uart_init(UART_BAUD_8MHz_38400);
	nrf24_init();
	nrf24_config(sizeof(uint8_t), 2);
	
	setLow(DDRD, 7);
	setHigh(PORTD, 7);
	
	//uint8_t data[32];
	uint8_t cfg, st, rf;

	nrf24_prepare_rx();

	while (1)
	{
		if (bitIsLow(PIND, 7))
		{
			uart_send_str("Read.. ");
			cfg = nrf24_read_register(NRF24_REGISTER_CONFIG);
			st = nrf24_read_status();
			rf = nrf24_read_register(NRF24_REGISTER_OBSERVE_TX);
			uart_send_str("cfg: ");
			uart_send_int(cfg);
			uart_send_str(" status: ");
			uart_send_int(st);
			uart_send_char('\n');
			if (st & NRF24_RX_DR)
			{
				nrf24_clear_status();
			}
			_delay_ms(10);
		}
	}
}
