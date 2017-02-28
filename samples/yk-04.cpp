#define F_CPU	8000000UL


#include <avr/io.h>
#include <util/delay.h>
#include <MemMath.h>

int main( void )
{
	DDRB = 0x02;
	PORTB = 0x00;
	
	while (1)
	{
		if (__bitIsHigh(PINB, 0))
		{
			if (__bitIsHigh(PINB, 1))
			{
				PORTB &= 0xFD;
			}
			else
			{
				PORTB |= 0x02;
			}
		}
		_delay_ms(1000);
	}	
	
	return 0;
}
