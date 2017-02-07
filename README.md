# AVRC

Library for AVR microcontrollers' programming.

Classes helps you to write AVR microcontrollers' code on programmer-friendly laguage :)

All code wrote in .h headers files, so .HEX size has minimal difference with plain C-code. You can easly use this library with any other libraries.

Library grants easy access to: UART, SPI, NRF24L01+, LED manipulations, Bit mathematics

Currently in progress: ESP8266
	

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
			led_turn_off(PORTB, 0);
		}
	}

