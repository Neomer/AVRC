#define F_CPU	8000000UL

#include <interface/uart.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define NEC_PORT	PORTB
#define NEC_PIN		0

#define NEC_START_HIGH		_delay_us(4500)
#define NEC_START_LOW		_delay_us(4500)
#define NEC_BIT_MARK		_delay_us(560)
#define NEC_ZERO			_delay_us(560)
#define NEC_ONE				_delay_us(1690)
#define NEC_RESTART			_delay_us(2500)

#define TIMER_ON		setHigh(TCCR2, COM20)
#define TIMER_OFF		setLow(TCCR2, COM20)

#define NEC_HIGH		setHigh(PORTB,3);
#define NEC_LOW			setLow(PORTB,3);

inline void nec_high(uint32_t time)
{
	TIMER_ON;
	_delay_us(time);
}

inline void nec_low(uint32_t time)
{
	TIMER_OFF;
	_delay_us(time);
}

void nec_send_byte(uint8_t data)
{
	for (int i = 0; i < 8; i++)
	{
		TIMER_ON;
		NEC_BIT_MARK;
		TIMER_OFF;
		if (bitIsHigh(data, i))
			NEC_ONE;
		else
			NEC_ZERO;
	}
}

void nec_send_byte_rev(uint8_t data)
{
	for (int i = 7; i >= 0; i--)
	{
		TIMER_ON;
		NEC_BIT_MARK;
		TIMER_OFF;
		if (bitIsHigh(data, i))
			NEC_ONE;
		else
			NEC_ZERO;
	}
}

void nec_send_samsung(uint8_t address, uint8_t command)
{
	nec_high(4500);
	nec_low(4500);
	
	nec_send_byte(address);
	nec_send_byte(address);
	nec_send_byte(command);
	nec_send_byte(~command);
	
	TIMER_ON;
	NEC_BIT_MARK;
	TIMER_OFF;
	NEC_RESTART;
}

ISR(TIMER2_COMP_vect)
{
	if (bitIsHigh(PINB, 3))
		setLow(PORTB, 3);
	else
		setHigh(PORTB,3);
}

void initTimer2PWM( )
{
	DDRB |= (1<<3);								// OC2 pin as o/p
	TCCR2 = (1<<WGM21)|(1<<COM20)|(1<<CS20);	// CTC, toggle,div8
	OCR2 = 104;//F_CPU/1/2/38000 - 1;			// = 104
//	setHigh(TIMSK, OCIE2);
}


int main( void )
{
	setLow(PORTB, 0);
	setHigh(DDRB, 0);

	initTimer2PWM();
	
	while (1)
	{
		nec_send_samsung(0x07, 0x02);
		_delay_ms(2000);
	}

	return 0;
}
