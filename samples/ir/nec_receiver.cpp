#define F_CPU	8000000UL

#include <interface/uart.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define TIMER_ON	TCCR0 |= 0x05
#define TIMER_OFF	TCCR0 &= 0xF8

static bool tmr = false;
static bool first = true;
static uint8_t val = 0,
				address = 0,
				command = 0;
static uint8_t bit = 0, 
			   tsave = 0,
			   ovf = 0,
				byte = 0;

#define TIMER_STEP	0.128		// мсек на 1 тик таймера

ISR(INT0_vect)
{
	uint8_t ts;
	
	if (!tmr)
	{
		uart_send_str("S ");
		tmr = true;
		bit = 0;
		address = 0;
		command = 0;
		byte = 0;
		TIMER_ON;
		
//		waitHigh(PIND, 2);
//		tsave = TCNT0;
//		uart_send_int(tsave);
//		uart_send_char(' ');
//		if ((tsave - ts < 33)||(tsave - ts > 37))
//		{
//			TIMER_OFF;
//			TCNT0 = 0;
//			tmr = false;
//			uart_send_str("T\n");
//		}
	}
	else 
	{
		ts = TCNT0;
		uint8_t dt = ts - tsave;
		
		uart_send_int(dt);
		uart_send_char(' ');
//		tsave = ts;
		
//		return;
		
	
		if (dt >= 67)
		{
			uart_send_str("B ");
		}
		else 
		{
			if ((dt >= 16)&&(dt <= 18))
			{
				//uart_send_char('1');
				val |= 1 << bit;
			}
			else if ((dt >= 8)&&(dt <= 10)) 
			{
				//uart_send_char('0');
			}
			else
			{
//				uart_send_str(" (");
//				uart_send_int(dt);
//				uart_send_str(" )");
			}
			if (bit == 7)
			{
				switch (byte)
				{
					case 0:
						address = val;
						break;
						
					case 1:
						//if (address != val)
						//	uart_send_str("address check failed!");
						break;
						
					case 2:
						command = val;
						break;
						
					case 3:
						break;
				}
				uart_send_char('.');
				byte++;
				bit = 0;
				val = 0;
			}
			else
			{
				bit++;
			}
		}
		tsave = ts;
	}
}
//0         1          2          3
//12345678 90123456 78901234 56789012
//11100000 11100000 11010000 00101111
//11010000001011

ISR(TIMER0_OVF_vect)
{
	if (ovf < 2)
		ovf++;
	else			
	{
		TIMER_OFF;
		uart_send_str("E -- Address: ");
		uart_send_int(address);
		uart_send_str(" Command: ");
		uart_send_int(command);
		uart_send_char('\n');
		tmr = false;
		bit = 0;
		val = 0;
		tsave = 0;
		ovf = 0;
	}
}


int main( void )
{
	uart_init(UART_BAUD_8MHz_38400);
	
	setLow(PORTB, 0);
	setHigh(DDRB, 0);

	SREG |= (1<<7);
	GICR |= (1<<6);
	MCUCR |= (1<<1);
	TIMSK |= (1<<TOIE0);
	while (1)
	{
	}

	return 0;
}
