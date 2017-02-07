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
	spi_init_master();
	spi_ss_low;
	
	
	while (1)
	{
		spi_ss_low;
		_delay_ms(20);
		uint8_t dev_id = spi_exchange( BMP280_REG_CHIPID | 0x80 );
		_delay_ms(20);
		spi_ss_high;
		
		uart_send_int(dev_id);
		_delay_ms(1000);
	}
	
	return 0;
}
