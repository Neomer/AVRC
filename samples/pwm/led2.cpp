#define F_CPU	9600000UL

#include <avr/io.h>
#include <avr/iotn13.h>

#include <avr/interrupt.h>
#include <util/delay.h>
#include <MemMath.h>
#include <actors/led_c.h>

#define LED_PIN			0
#define SENSOR_PIN		4
#define PWM_STEP_1		50
#define PWM_STEP_2		5
#define PWM_STEP_3		2
#define STATE_TIMEOUT	2000
#define TIMER_OVF_LIMIT	3000

volatile static bool light = false;
volatile static int tim_ovf = 0;
volatile static bool tim_run = false;

inline void start_timer() 
{
	//TCCR0B |= 0x05;
}

inline void stop_timer() 
{
	//TCCR0B &= 0xF8;
}

inline void led_on( void )
{
	for (int i = 0; i < 20; i++)
	{
		OCR0A = i;
		_delay_ms(PWM_STEP_1);
	}
	for (int i = 20; i < 150; i++)
	{
		OCR0A = i;
		_delay_ms(PWM_STEP_2);
	}
	for (int i = 150; i < 255; i++)
	{
		OCR0A = i;
		_delay_ms(PWM_STEP_3);
	}
	OCR0A = 0xff;
}

inline void led_off( void )
{
	for (int i = 254; i >= 0; i--)
	{
		OCR0A = i;
		_delay_ms(PWM_STEP_2);
	}
	OCR0A = 0;
}

ISR(INT0_vect)
{
	light = true;
	tim_run = true;
	tim_ovf = 0;
}

ISR(TIM0_OVF_vect)
{
	tim_ovf++;
	if (tim_ovf == TIMER_OVF_LIMIT)
	{
		light = false;
		tim_run = false;
		tim_ovf = 0;
	}
}



inline void initPWM()
{
	TCCR0A=0xB1;
	TCCR0B=0x03;
	TCNT0=0x00;
	OCR0A=0x00;
	OCR0B=0x00;
	TIMSK0|=1 << TOIE0;
}

inline void initInt()
{
	GIFR |= 1 << INTF0;
	GIMSK |= 1 << INT0;
}

int main()
{
	setHigh(DDRB, LED_PIN);
	setHigh(PORTB, LED_PIN);

	setLow(DDRB, SENSOR_PIN);
	setLow(PORTB, SENSOR_PIN);
	
	initPWM();
	initInt();

	sei();
	
	while (1)
	{
		if (tim_run)
		{
			led_on();
			while (tim_run);
			led_off();
		}
	}
	
	return 0;
}
