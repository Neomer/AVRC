#define F_CPU		8000000UL

#include <interface/i2c.h>
#include <interface/uart.h>
#include <avr/interrupt.h>
#include <util/delay.h>

//#include <avr/iom8.h>

ISR(TWI_vect)
{
	cli();
	
	uint8_t status = TWSR;
	
	switch (status & I2C_STATUS_MASK)
	{
		case I2C_STATUS_SR_RX_ADR_ACK: case I2C_STATUS_MT_RX_ADR_NACK:
			uart_send_char('A');
			TWCR |= (0<<TWSTO)|(1<<TWEA)|(1<<TWINT);
			break;
		
		case I2C_STATUS_SR_RX_DATA_ACK: case I2C_STATUS_SR_RX_DATA_NACK:
			TWCR |= (0<<TWSTO)|(1<<TWEA)|(1<<TWINT);
			uart_send_int(TWDR);
			uart_send_char(' ');
			break;
			
		case I2C_STATUS_SR_RX_STOP_RESTART:
			uart_send_char('E');
			TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
			break;

		default:
			uart_send_int(status);
			uart_send_char(' ');
			TWCR |= (0<<TWSTO)|(1<<TWEA)|(1<<TWINT);
			break;
	}
	sei();
}

int main()
{

	uart_init(UART_BAUD_8MHz_38400);
	i2c_init_slave(I2C_SPEED_8MHz_100KHz, 0x02);

	uart_send_str("start\n");
	
	sei();
	
	while (1)
	{
		
	}
}
