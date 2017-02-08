#define F_CPU	8000000UL

#define  SPI_PORT			PORTB
#define  SPI_DDR			DDRB
#define  SPI_MOSI			3
#define  SPI_SCK			5
#define  SPI_SS				2
#define  SPI_MISO			4


#include <abstract/spi.h>
#include <abstract/uart.h>
#include <sensors/bmp280.h>

int main( void )
{
	uart_init(UART_BAUD_8MHz_38400);
	bmp280_init();
	bmp280_register_write(BMP280_REG_RESET, BMP280_POWER_ON_RESET);
	_delay_ms(100);
	uint8_t cfg = bmp280_register_read(BMP280_REG_CONFIG);
	__setHigh(cfg, 0);
	bmp280_register_write(BMP280_REG_CONFIG, cfg);
	_delay_ms(100);
	
	
	while (1)
	{
		uint8_t dev_id = bmp280_register_read(BMP280_REG_CHIPID);
		if (dev_id != 0xff)
		{
			uart_send_int(dev_id);
		}
		_delay_ms(1000);
	}
	
	return 0;
}
