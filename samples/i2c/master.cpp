#define F_CPU		8000000UL

#include <interface/uart.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>

#define I2C_PORT		PORTC
#define I2C_DDR			DDRC
#define I2C_PIN			PINC
#define I2C_SCL			5
#define I2C_SDA			4
#define I2C_TIMEOUT		2			
#include <interface/i2c_soft.h>

#define I2C_ADDRESS		0x77

int main()
{
	uart_init(UART_BAUD_8MHz_38400);
	i2csoft_init_master();
	
	volatile uint8_t b[22];
	uint16_t AC5, AC6;
	int16_t	MC, MD;
	
	int32_t x1, x2;
	
	uint16_t ut, t;
	while (1)
	{
		for (uint8_t add = 0xAA; add <= 0xBF; add++)
		{
			i2csoft_start();
			i2csoft_open_write(I2C_ADDRESS);
			i2csoft_write_byte(add);
			i2csoft_start();
			i2csoft_open_read(I2C_ADDRESS);
			b[add - 0xAA] = i2csoft_read_byte(0);
		}
		AC5 = (b[8] << 8) | b[9];
		AC6 = (b[10] << 8) | b[11];
		MC  = (b[18] << 8) | b[19];
		MD  = (b[20] << 8) | b[21];
		uart_send_str("AC5=");
		uart_send_int(AC5);
		uart_send_str(" AC6=");
		uart_send_int(AC6);
		uart_send_str(" MC=");
		uart_send_int(MC);
		uart_send_str(" MD=");
		uart_send_int(MD);
		uart_send_char('\n');
		
		i2csoft_start();
		i2csoft_open_write(I2C_ADDRESS);
		i2csoft_write_byte(0xF4);
		i2csoft_write_byte(0x2E);
		_delay_ms(5);
		i2csoft_start();
		i2csoft_open_write(I2C_ADDRESS);
		i2csoft_write_byte(0xF6);
		i2csoft_start();
		i2csoft_open_read(I2C_ADDRESS);
		ut = i2csoft_read_byte(0) << 8;
		i2csoft_start();
		i2csoft_open_write(I2C_ADDRESS);
		i2csoft_write_byte(0xF7);
		i2csoft_start();
		i2csoft_open_read(I2C_ADDRESS);
		ut = ut + i2csoft_read_byte(0);
		i2csoft_stop();
		uart_send_str("UT=");
		uart_send_int(ut);
		x1 = (ut - 21518) * 0.752105712890625;
		uart_send_str(" X1=");
		uart_send_int(x1);
		x2 = -24137728 / (x1 + 3036);
		uart_send_str(" X2=");
		uart_send_int(x2);
		t = (x1 + x2 + 8) / 16;
		uart_send_str(" T=");
		uart_send_int(t);
		uart_send_char('\n');
		_delay_ms(2000);
	}
}
