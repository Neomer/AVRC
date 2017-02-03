#define F_CPU	8000000UL

#include <avr/io.h>
#include <util/delay.h>

#define high_mask 1 << 2
#define low_mask ~(1 << 2)

int main()
{
	uint8_t data[5];
		
	while (1)
	{
//		DDRB |= high_mask;
//		PORTB &= low_mask;
//		_delay_ms(50);
//		PORTB |= high_mask;
//		DDRB &= low_mask;
//		while ((PINB  & high_mask) != 0);
//		while ((PINB  & high_mask) == 0);
//		while ((PINB  & high_mask) != 0);
//		for (int b = 0; b < 5; b++)
//		{
//			for (int bit = 0; bit < 8; bit++)
//			{
//				while ((PINB  & (1 << 2)) == 0);
//				_delay_us(50);
//				if ((PINB  & (1 << 2)) != 0)
//					data[b] |= 1 << (7 - bit);
//				while ((PINB  & (1 << 2)) != 0);
//			}
//		}
//		_delay_us(70);
//		DDRB |= 1 << 2;
//		PORTB |= 1 << 2;
			
//		if (data[0] + data[1] + data[2] + data[3] != data[4])
//		{
//			humidity = data[0] + data[1] * 0.01,
//			temperature = data[2] + data[3] * 0.01;
//		}
	}
}
