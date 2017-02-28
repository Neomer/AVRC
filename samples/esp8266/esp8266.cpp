#define F_CPU	8000000UL

#include <interface/uart.h>
#include <util/delay.h>
#include <abstract/Queue.h>

int main( void )
{
	uart_init(UART_BAUD_8MHz_115200);
	
	uint8_t b;
	QUEUE(10) data;
	while (1)
	{
		b = uart_read_char();
		uart_send_str("Received: ");
		uart_send_char(b);
		uart_send_char('\n');
			
		_delay_ms(50);
	}
	
	return 0;
}
