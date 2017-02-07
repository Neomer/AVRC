#define F_CPU	8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <MemMath.h>
#include <actors/led_c.h>

inline void led_on( void )
{
	__setHigh(TCCR2, 0);
	for (int i = 0; i < 255; i++)
	{
		OCR2 = i;
		_delay_ms(50);
	}
	OCR2 = 0xff;
	__setLow(TCCR2, 0);
}

inline void led_off( void )
{
	__setHigh(TCCR2, 0);
	for (int i = 254; i >= 0; i--)
	{
		OCR2 = i;
		_delay_ms(50);
	}
	OCR2 = 0;
	__setLow(TCCR2, 0);			
}

int main()
{
	//TCCR2 = 0b01101000;
	//TCNT2 = 0x00;
	//OCR2  = 0x00;
	
	__setHigh(DDRB, 3);
	
	__setLow(DDRC, 5);
	__setLow(PORTC, 5);
	
	__setLow(DDRB, 2);
	__setLow(PORTB, 2);
	
	bool isLight = false;
	
	while (1)
	{
		if (__bitIsLow(PINB, 2))
		{
			led_turn_off(PORTB, 3);
			isLight = false;
		}
		else 
		{
			if (__bitIsHigh(PINC, 5))
			{
				if ((!isLight))
				{
					led_turn_on(PORTB, 3);
					isLight = true;
				}
			}
			else
			{
				if (isLight)
				{
					
					led_turn_off(PORTB, 3);
					isLight = false;
				}
			}
		}
		
		_delay_ms(100);
	}
	
	return 0;
}
