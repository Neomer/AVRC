#define F_CPU		8000000UL

#include <interface/i2c.h>
#include <interface/i2c_soft.h>
#include <interface/uart.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//#include <avr/iom8.h>

ISR(INT0_vect)
{
	
}

int main()
{
	uart_init(UART_BAUD_8MHz_38400);

	
	
	sei();
	
	while (1)
	{

	}
}
