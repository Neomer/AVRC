#define F_CPU		8000000UL

#include <interface/i2c.h>
#include <interface/i2c_soft.h>
#include <interface/uart.h>
#include <avr/interrupt.h>
#include <util/delay.h>

static uint8_t sbuf[] = {0x04, 0x01, 0x00, 0x30, 0xff, 0xcd};
static uint8_t sbuf_idx = 0;

#define I2C_ADDRESS		0x02

int main()
{
	uart_init(UART_BAUD_8MHz_38400);
	i2csoft_init_master();

	while (1)
	{
		i2csoft_start();
		i2csoft_write_byte(I2C_ADDRESS);
		i2csoft_write_byte(0x04);
		i2csoft_write_byte(0x01);
		i2csoft_write_byte(0x00);
		i2csoft_write_byte(0x30);
		i2csoft_write_byte(0xff);
		i2csoft_write_byte(0xcd);
		i2csoft_stop();
		uart_send_char('<');
		uart_send_char(i2csoft_read_byte());
		_delay_ms(5000);
	}
}
