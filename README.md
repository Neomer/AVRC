# AVRC

Library for AVR microcontrollers' programming.

Classes helps you to write code for loading in AVR microcontrollers.

Code sample:

	ControllerM8 c;
	LED led(avr_bit_s(iPB, 0), &c);
	
	Potentiometer pot(avr_bit_s(iPC, 0), &c);
	
	while (1)
	{
		if (pot.half())
		{
			led.turnOn();
		}
		else
		{
			led.turnOff();
		}
		
		_delay_ms(10);
	}
