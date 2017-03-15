#define F_CPU	8000000UL

#include <interface/uart.h>
#include <interface/i2c.h>

int main( void )
{
	i2c_init_master(I2C_SPEED_8MHz_400KHz);
	uart_init(UART_BAUD_8MHz_38400);
	
	uart_send_str("start\n");
	volatile uint8_t t;
	while (1)
	{
		i2c_start();
		i2c_open_write(0x77);
		i2c_write_byte(0xD0);
		i2c_start();
		i2c_open_read(0x77);
		t = i2c_read_byte();
		i2c_stop();
		uart_send_int(t);
		uart_send_char(' ');
		_delay_ms(2000);

	}
	
	return 0;
}
