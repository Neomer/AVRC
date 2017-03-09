#define F_CPU	9600000UL

#include <avr/io.h>

#include <util/delay.h>
#include <MemMath.h>
#include <actors/led_c.h>

#define LED_PIN			0
#define SENSOR_PIN		4
//#define PWM_STEP		5
//#define STATE_TIMEOUT	2000

//inline void led_on( void )
//{
//	for (int i = 0; i < 255; i++)
//	{
//		OCR0A = i;
//		_delay_ms(PWM_STEP);
//	}
//	OCR0A = 0xff;
//}

//inline void led_off( void )
//{
//	for (int i = 254; i >= 0; i--)
//	{
//		OCR0A = i;
//		_delay_ms(PWM_STEP);
//	}
//	OCR0A = 0;
//}

//inline void initPWM()
//{
//	TCCR0A=0b11000011;
//	TCCR0B=0b00000101;
//	TCNT0=0x00;
//	OCR0A=0x00;
//	OCR0B=0x00;
//	TIMSK0=0x00;
//}

int main()
{
	setHigh(DDRB, LED_PIN);
	setHigh(PORTB, LED_PIN);

	setLow(DDRB, SENSOR_PIN);
	setLow(PORTB, SENSOR_PIN);
	
	initPWM();
	
	while (1)
	{
		led_on();
		_delay_ms(STATE_TIMEOUT);
		led_off();
		_delay_ms(STATE_TIMEOUT);
	}
	
	return 0;
}
