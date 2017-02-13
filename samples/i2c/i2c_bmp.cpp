#define F_CPU	8000000UL

#include <interface/uart.h>
#include <sensors/bmp280.h>
#include <util/twi.h>

int main( void )
{
	// 50000 speed
	bmp280_i2c_init(72);
	uart_init(UART_BAUD_8MHz_38400);
	
	__setLow(DDRB, 0);
	__setHigh(PORTB, 0);
	
	while (1)
	{
		if (__bitIsLow(PINB, 0))
		{
			uart_send_char('#');
			uint8_t reg = bmp280_i2c_register_read(BMP280_REG_CHIPID);
			if (reg)
				uart_send_char(reg);
			_delay_ms(1000);
		}
	}
	
	return 0;
}
