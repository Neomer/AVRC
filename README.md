# AVRC

Library for AVR microcontrollers' programming.

Classes helps you to write AVR microcontrollers' code on programmer-friendly laguage :)

#Code sample

	int main()
	{
		led(DDRB, 0);
	
		uart_init(UART_BAUD_8MHz_38400);
		nrf24_init();
		nrf24_config(sizeof(uint8_t), 2);
	
		uint8_t b;
		while (1)
		{
			led_turn_on(PORTB, 0);
			nrf24_send_char('#');
			__setLow(PORTB, 0);
			led_turn_off(PORTB, 0);
		}
	}

