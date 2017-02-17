#define F_CPU	8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <MemMath.h>
#include <actors/led_c.h>

inline void led_on( void )
{
	setHigh(TCCR2, 0);
	for (int i = 0; i < 255; i++)
	{
		OCR2 = i;
		_delay_ms(50);
	}
	OCR2 = 0xff;
	setLow(TCCR2, 0);
}

inline void led_off( void )
{
	setHigh(TCCR2, 0);
	for (int i = 254; i >= 0; i--)
	{
		OCR2 = i;
		_delay_ms(50);
	}
	OCR2 = 0;
	setLow(TCCR2, 0);			
}

int main()
{
	//TCCR2 = 0b01101000;
	//TCNT2 = 0x00;
	//OCR2  = 0x00;
	
	setHigh(DDRB, 3);
	
	setLow(DDRC, 5);
	setLow(PORTC, 5);
	
	setLow(DDRB, 2);
	setLow(PORTB, 2);
	
	bool isLight = false;
	
	while (1)
	{
		if (bitIsLow(PINB, 2))
		{
			led_turn_off(PORTB, 3);
			isLight = false;
		}
		else 
		{
			if (bitIsHigh(PINC, 5))
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
