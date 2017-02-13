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
	nrf24_set_data_length(0, sizeof(uint8_t));
	

	__setLow(DDRD, 7);
	__setHigh(PORTD, 7);
	
	uint8_t b;
	uint8_t cfg, st, rf;
	while (1)
	{
		if (__bitIsLow(PIND, 7))
		{
			uart_send_str("Send.. ");
			nrf24_send_char('#');
			uart_send_str("Read.. ");
			cfg = nrf24_read_register(NRF24_REGISTER_CONFIG);
			st = nrf24_read_status();
			rf = nrf24_read_register(NRF24_REGISTER_OBSERVE_TX);
			uart_send_str("Config: ");
			uart_send_int(cfg);
			if (__bitIsHigh(cfg, NRF24_MASK_RX_DR))
				uart_send_str("\n   RX_DR: ON");
			else
				uart_send_str("\n   RX_DR: OFF");
			if (__bitIsHigh(cfg, NRF24_MASK_TX_DS))
				uart_send_str("\n   TX_DS: ON");
			else
				uart_send_str("\n   TX_DS: OFF");
			if (__bitIsHigh(cfg, NRF24_MASK_MAX_RT))
				uart_send_str("\n   MAX_RT: ON");
			else
				uart_send_str("\n   MAX_RT: OFF");
			if (__bitIsHigh(cfg, NRF24_EN_CRC))
				uart_send_str("\n   EN_CRC: ON");
			else
				uart_send_str("\n   EN_CRC: OFF");
			if (__bitIsHigh(cfg, NRF24_CRCO))
				uart_send_str("\n   CRCO: ON");
			else
				uart_send_str("\n   CRCO: OFF");
			if (__bitIsHigh(cfg, NRF24_PWR_UP))
				uart_send_str("\n   PWR_UP: ON");
			else
				uart_send_str("\n   PWR_UP: OFF");
			if (__bitIsHigh(cfg, NRF24_PRIM_RX))
				uart_send_str("\n   PRIM_RX: ON");
			else
				uart_send_str("\n   PRIM_RX: OFF");
			
			uart_send_str("\nStatus: ");
			uart_send_int(st);
			if (__bitIsHigh(st, NRF24_RX_DR))
				uart_send_str("\n   RX_DR: ON");
			else
				uart_send_str("\n   RX_DR: OFF");
			if (__bitIsHigh(st, NRF24_TX_DS))
				uart_send_str("\n   TX_DS: ON");
			else
				uart_send_str("\n   TX_DS: OFF");
			if (__bitIsHigh(st, NRF24_MAX_RT))
				uart_send_str("\n   MAX_RT: ON");
			else
				uart_send_str("\n   MAX_RT: OFF");
			uart_send_str("\n   RX_PIPE: ");
			uart_send_int((st & NRF24_RX_PIPE_MASK) >> NRF24_RX_PIPE);
			if (__bitIsHigh(st, NRF24_TX_FULL0))
				uart_send_str("\n   TX_FULL0: ON");
			else
				uart_send_str("\n   TX_FULL0: OFF");
			
			uart_send_str("\nTransimission state: Packets lost: ");
			uart_send_int((rf & NRF24_PLOS_CNT_MASK) >> 4);
			uart_send_str(" retransmitted: ");
			uart_send_int((rf & NRF24_ARC_CNT_MASK));
			uart_send_char('\n');
			
			if (st & NRF24_MAX_RT)
			{
				nrf24_write_register(NRF24_REGISTER_STATUS, st);
			}
			_delay_ms(500);
		}
	}
}
