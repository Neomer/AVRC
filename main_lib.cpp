#define F_CPU	8000000UL

#include "abstract/Controller.h"
#include "dev/m8/MemoryM8.h"
#include "actors/LED.h"

int main()
{
	IController c;
	LED led(avr_bit_s(iPB, 0), &c);
	
	while (1) 
	{
		led.turnOn();
		led.turnOff();
	}
}
