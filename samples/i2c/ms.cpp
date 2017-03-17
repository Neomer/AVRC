#define F_CPU		8000000UL

#include <interface/i2c.h>
#include <interface/i2c_soft.h>
#include <interface/uart.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>

#define I2C_ADDRESS		0x02

ISR(TWI_vect)
{
	cli();
	
	uint8_t status = TWSR;
	uint8_t b;
	char s[4];
	s[3] = 0;
	_delay_ms(1);

	switch (status & I2C_STATUS_MASK)
	{
		case I2C_STATUS_SR_RX_ADR_ACK:/* case I2C_STATUS_SR_RX_ADR_NACK:*/
			uart_send_str("-AW:");
			uart_send_int( TWDR );
			i2csoft_start();
			i2csoft_open_write(I2C_ADDRESS);
			break;
		
		case I2C_STATUS_SR_RX_DATA_ACK:/* case I2C_STATUS_SR_RX_DATA_NACK:*/
			b = TWDR;
			sprintf(s, " %.2X", b);
			uart_send_str(s);
			i2csoft_write_byte(b);
			break;

		case I2C_STATUS_SR_RX_STOP_RESTART:
			uart_send_str("E\n");
			_delay_ms(10);
			do
			{
				_delay_us(5);
				i2csoft_start();
			}
			while (!i2csoft_open_read(I2C_ADDRESS));
			break;
			
		case I2C_STATUS_BUS_ERROR:
			uart_send_str("B\n");
			break;

		case TW_ST_SLA_ACK:		// 0xA8: SLA+R received, ACK returned
			uart_send_str("-AR:");
			uart_send_int( TWDR );
			b = i2csoft_read_byte();
			sprintf(s, " %.2X", b);
			uart_send_str(s);
			TWDR = b;
			break;
			
        case TW_ST_DATA_ACK:    // 0xB8: data transmitted, ACK received
			b = i2csoft_read_byte();
			sprintf(s, " %.2X", b);
			uart_send_str(s);
			TWDR = b;
            break;
 
        case TW_ST_DATA_NACK:   // 0xC0: data transmitted, NACK received
        case TW_ST_LAST_DATA:   // 0xC8: last data byte transmitted, ACK received
			b = i2csoft_read_byte(false);
			uart_send_str("L\n");
			break;
			
		default:
			uart_send_char('U');
			uart_send_int(status);
			uart_send_char(' ');
			break;
	}
	TWCR |= (1<<TWINT);
//	uart_send_char('\n');
	sei();
}

int main()
{

	uart_init(UART_BAUD_8MHz_38400);
	i2c_init_slave(I2C_SPEED_8MHz_100KHz, I2C_ADDRESS);
	i2csoft_init_master();

	sei();
	while (1)
	{
		
	}
}
