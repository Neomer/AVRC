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
#define  SPI_SS				1
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

#define AVRC_INTERRUPT
#include <connectors/nRF24L01.h>


ISR(NRF24_IRQ_INT)
{
	uint8_t st = nrf24_read_status();
	uart_send_str("Interrupt!\n");
	uart_send_str("Status: ");
	uart_send_int(st);
	uart_send_char('\n');
	if (__bitIsHigh(st, NRF24_TX_DS))
	{
		uart_send_str("Tx ready!\n");
	}
	if (__bitIsHigh(st, NRF24_RX_DR))
	{
		uart_send_str("Rx ready!\n");
	}
	if (__bitIsHigh(st, NRF24_MAX_RT))
	{
		uart_send_str("Data not sent!\n");
	}
}

int main()
{
	led(DDRB, 0);
	
	uart_init(UART_BAUD_8MHz_38400);
	nrf24_init();
//	nrf24_set_output_power(NRF24_RF_PWR_0db);
	nrf24_config(sizeof(uint8_t), 2);

	MCUCR |= (1 << ISC00) | (1 << ISC01);
	GICR |= (1<<INT0);
	sei();
	
	__setLow(DDRD, 7);
	__setHigh(PORTD, 7);
	
	uint8_t b;
	while (1)
	{
		if (__bitIsLow(PIND, 7))
		{
			nrf24_send_char('#');
			uint8_t cfg = nrf24_read_register(NRF24_REGISTER_CONFIG);
			uint8_t st = nrf24_read_status();
			uint8_t rf = nrf24_read_register(NRF24_REGISTER_RF_SETUP);
			uart_send_str("cfg: ");
			uart_send_int(cfg);
			uart_send_str(" status: ");
			uart_send_int(st);
			uart_send_str(" rf setup: ");
			uart_send_int(rf);
			uart_send_char('\n');
			_delay_ms(3000);
		}
	}
}
