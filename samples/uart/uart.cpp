#define F_CPU	8000000UL

#include <interface/uart.h>
#include <util/delay.h>

int main( void )
{
	uart_init(UART_BAUD_8MHz_38400);
	
	while (1)
	{
		uart_send_char('#');
		
		_delay_ms(500);
	}
	
	return 0;
}
