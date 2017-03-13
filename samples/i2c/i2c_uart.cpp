#define F_CPU	8000000UL

#include <interface/uart.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/iom8.h>

static bool tmr = true;
static bool ack = false;

static uint32_t ovf = 0;
static uint8_t buf = 0,
				shift = 0;


//1000101000000
ISR(INT0_vect)
{
	cli();
	tmr = !tmr;
	if (tmr)
	{
		if (ack)
		{
			ack = false;
		}
		else
		{
			if (bitIsHigh(PINB, 0))
			{
				buf |= (1 << shift);
			}
			if (shift == 7)
			{
				uart_send_char(buf);
				buf = 0;
				shift = 0;
				ack = true;
			}
			else
			{
				shift++;
			}
		}
	}
	sei();
}


int main( void )
{
	uart_init(UART_BAUD_8MHz_38400);
	
	setLow(DDRB, 0);

	SREG |= (1<<7);
	GICR |= (1<<6);
	MCUCR &= 0xF1;
	while (1)
	{
		//uart_send_char(bitIsHigh(PINB, 0));
	}

	return 0;
}
