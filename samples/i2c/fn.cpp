#define F_CPU		8000000UL

#include <interface/uart.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

#define I2C_PORT		PORTC
#define I2C_DDR			DDRC
#define I2C_PIN			PINC
#define I2C_SCL			1
#define I2C_SDA			0
#define I2C_TIMEOUT		2			
#include <interface/i2c_soft.h>

#define I2C_ADDRESS		0x02
static uint8_t buf[] = { 0x04, 0x01, 0x00, 0x30, 0xff, 0xcd };


int main()
{
	uart_init(UART_BAUD_8MHz_38400);
	i2csoft_init_master();
	
	bool f;
	uint8_t b = 0, l = 0;
	while (1)
	{
		uart_send_char('S');
		i2csoft_start();
		uart_send_char('A');
		if (i2csoft_open_write(I2C_ADDRESS))
		{
			uart_send_char('W');
			i2csoft_write_byte(0x04);
			i2csoft_write_byte(0x01);
			i2csoft_write_byte(0x00);
			i2csoft_write_byte(0x30);
			i2csoft_write_byte(0xFF);
			i2csoft_write_byte(0xCD);
			do
			{
				_delay_ms(1);
				uart_send_char('E');
				i2csoft_start();
				uart_send_char('R');
				f = i2csoft_open_read(I2C_ADDRESS);
			}
			while (!f);
			uart_send_char('<');
			b = i2csoft_read_byte();
			uart_send_int( b );
			if (b == 0x04)
			{
				uart_send_char('<');
				l = i2csoft_read_byte();
				uart_send_int( l );
				for (uint8_t i = l; i > 1; i--)
				{
					uart_send_char('<');
					uart_send_int( i2csoft_read_byte() );
				}
				uart_send_char('<');
				uart_send_int( i2csoft_read_byte(0) );
			}
		}
		i2csoft_stop();
		uart_send_char('\n');
		_delay_ms(2000);
	}
}
