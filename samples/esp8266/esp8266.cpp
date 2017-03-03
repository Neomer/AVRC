#define F_CPU	8000000UL

#include <interface/uart.h>
#include <util/delay.h>
#include <abstract/Queue.h>
#include <abstract/FIFO.h>
#include <string.h>
#include <abstract/nec.h>
#include <actors/led_c.h>

#define ESP8266_IPD_LENGTH		4
#define BUFFER_LENGTH			50
#define PKG_LEN					4

#define waitEndl				while (uart_read_char() != '\n')

int main( void )
{
	uart_init(UART_BAUD_8MHz_38400);
	nec_init();
	
	_delay_ms(5000);
	uint8_t b[50];
	bool failed = false;
	uint8_t idx = 0;
	uint8_t c[ESP8266_IPD_LENGTH];
	
	uart_send_str("ATE0\r\n");
	waitEndl;
	_delay_ms(50);

	uart_send_str("AT+CIPSTART=\"TCP\",\"192.168.88.244\",9875\r\n");
	waitEndl;
	_delay_ms(1000);
	
	setHigh(DDRB, 0);
	setLow(PORTB, 0);
	volatile uint8_t sym;
			
	while (1)
	{
		idx = 0;
		sym = uart_read_char();
		uart_send_char(sym);
//		while ((sym != '\n')&&(idx < BUFFER_LENGTH))
//		{
//			b[idx++] = sym;
//			sym = uart_read_char();
//		}
//		uart_send_array(b, idx);
		
//		if (!memcmp(b, "+IPD", ESP8266_IPD_LENGTH))
//		{
//			led_turn_on(PORTB, 0);
//			_delay_ms(1000);
//			led_turn_off(PORTB, 0);
//			_delay_ms(1000);
			
//			int st = 0;
//			for (st; st < idx; st++)
//			{
//				if (b[st] == ':')
//					break;
//			}
//			memcpy(c, b, st - ESP8266_IPD_LENGTH - 1);
//			c[st - ESP8266_IPD_LENGTH] = 0;
//			uart_send_str((const char *)c);
//			if (atoi((const char *)c) == 1)
//			{
//				led_turn_on(PORTB, 0);
//				_delay_ms(500);
//				led_turn_off(PORTB, 0);
//				_delay_ms(500);
//				led_turn_on(PORTB, 0);
//				_delay_ms(500);
//				led_turn_off(PORTB, 0);
//				_delay_ms(500);
//			}
//		}
	}
	
	return 0;
}
