#define F_CPU	8000000UL

#include <interface/uart.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/iom8.h>

#define I2C_SDA			0
#define I2C_SDA_PIN		PINB

static volatile uint8_t buf = 0;
static uint8_t idx = 7;
static bool ack = false;
static bool first = true;
static char b[1024];

/*
11000000 0 00000000 1 00000000 0 01100000 1 
11111001 0 0101001000011000000000100111100000000000000000000000110000000100000001000000010000000000000000000000100000001000000010000000101100100011001000110011011100010110000101101101011000000110010001000010110000101100001011000010110010001000000010111000100101000000010000000100000001000000011100010110001010000000000000100000000010000000000110000011111100100101001000011101000011000000000100111100000000000000000000000110000000100000001000000010000000000000000000000100000001000000010000000101100100011001000110011011100010110000101101101011000000110010001000010110000101100001011000010110010001000000010111101100101000000010000000100000000000000011000011100001001
3 0 1 24 124 36 4 1 100 1 0 0 3 2 2 2 0 0 1 1 1 77 76 76 14 6 54 6 38 66 67 67 67 19 1 29 41 32 32 32 96 104 20 0 4 16 0 65 79 74 56 48 0 60 0 0 96 64 64 64 0 0 32 32 32 32 9 9 89 81 80 86 64 68 104 104 104 104 34 32 55 5 4 4 0 12 7 
11000000 0 00000000 1 00000000 0 01110000 1 
11011001 0 010000100001100000000010000010000000001000001010011010110101100000000000000100000000010000000000110000011111100100101001000011101000011000000000100111100000000000000000000000110000000100000001000000010000000000000000000000100000001000000010000000101100100011001000110011011100010110000101101101011000000110010001000010110000101100001011000010110010001000000010111101100101000000010000000100000000000000011000011100001011
3 0 1 56 92 36 4 1 4 1 4 101 45 1 0 0 2 48 120 73 9 23 6 16 7 0 0 12 8 8 8 0 0 4 4 4 52 49 49 59 26 90 26 24 8 13 13 13 77 4 116 38 0 0 0 0 97 80 
11000000 0 00000000 1 00000000 0 01101100 0 
11000001 1 10100100001100000000010000010000000000000001010011011110101101000010000000000000000100000000000110000111111101101101011000011101000011000000000100111100000000000000000000000110000000100000001000000010000000000000000000000100000001000000010000000101100100011001000110011011100010110000101101101011000000110010001000010110000101100001011000010110010001000000010111101100101000000010000000100000000000000011000011100001001
3 0 1 88 48 56 4 1 4 1 0 101 47 5 0 0 1 48 124 109 13 23 6 16 7 0 0 12 8 8 8 0 0 4 4 4 52 49 49 59 26 90 26 24 8 13 13 13 77 4 116 38 0 0 0 0 97 16 
11000000 0 00000000 1 00000000 0 01101100 0 
01100000 1 11010010000110000000001000001000000000000000101001100111010110100001000000000000000010000000000110000011111100100101001000011101000011000000000100111100000000000000001000000010000000100000001000000000000000000000010000000100000001000000010000000001100100011001101110001011101010110000101111100011000000110011011000010110000101100001011000000100010001000010110110101100001000000010000000000000000000000111000001100000101
3 0 1 88 48 56 4 1 4 1 0 101 46 5 0 0 1 24 124 36 4 11 3 72 3 0 4 4 4 4 0 0 2 2 2 2 24 24 29 93 13 125 12 76 6 6 6 6 34 66 91 67 64 0 0 96 96 80 
*/
ISR(INT0_vect)
{
//	if (first)
//	{
//		first = false;
//		return;
//	}
//	cli();
	if (buf < 0xff)
		b[buf++] = bitIsHigh(I2C_SDA_PIN, I2C_SDA);
//	sei();
}


int main( void )
{
	uart_init(UART_BAUD_8MHz_38400);
	
	setLow(DDRB, 0);
	
	setLow(DDRB, 1);
	setHigh(PORTB, 1);

	SREG |= (1<<7);
	MCUCR |= 0x03;
	GICR |= (1<<6);
	
	while (1)
	{
		if (bitIsLow(PINB, 1))
		{
			if (buf > 0)
			{
				for (int i = 0; i < buf; i++)
				{
					if (b[i])
					{
						uart_send_char('1');
					}
					else
					{
						uart_send_char('0');
					}
				}
				uart_send_char('\n');
				uint8_t tmp = 0;
				int t = 0;
				int i = 0;
				while ( i < buf )
				{
					if (b[i])
					{
						tmp |= 1 << t;
					}
					t++;
					if ((i + 1) % 8 == 0)
					{
						uart_send_int(tmp);
						uart_send_char(' ');
						i++;
						t = 0;
						tmp = 0;
					}
					i++;
				}
				uart_send_char('\n');
				buf = 0;
			}
		}
	}

	return 0;
}
