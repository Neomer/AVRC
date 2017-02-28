#define F_CPU	8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <MemMath.h>
#include <actors/led_c.h>

int main()
{
	DDRB = 0b00001000;
	PORTB = 0b00000001;

	while (1)
	{
		if ((PINB & 0x01) == 0)
		{
			PORTB |= 1 << PB3;
		}
		else
		{
			PORTB &= ~(1 << PB3);
		}
	};
	
	return 0;
}
	
