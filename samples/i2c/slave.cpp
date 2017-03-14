#define F_CPU		8000000UL

#include <interface/i2c.h>
#include <interface/i2c_soft.h>
#include <interface/uart.h>
#include <avr/interrupt.h>
#include <util/delay.h>

static uint8_t sbuf[] = {0x04, 0x03, 0x00, 0x00, 0x02, 0x03, 0xdf, 0xa9};
static uint8_t sbuf_idx = 0;

#define I2C_ADDRESS		0x02

ISR(TWI_vect)
{
	cli();
	
	uint8_t status = TWSR;
	uint8_t b;
	switch (status & I2C_STATUS_MASK)
	{
		case I2C_STATUS_SR_RX_ADR_ACK: case I2C_STATUS_SR_RX_ADR_NACK:
			uart_send_char('A');
			sbuf_idx = 0;
			i2csoft_start();
			i2csoft_write_byte(I2C_ADDRESS);
			break;
		
		case I2C_STATUS_SR_RX_DATA_ACK: case I2C_STATUS_SR_RX_DATA_NACK:
			b = TWDR;
			uart_send_int(b);
			uart_send_char(' ');
			i2csoft_write_byte(b);			
			break;
			
			break;
		case I2C_STATUS_SR_RX_STOP_RESTART:
			uart_send_char('E');
			i2csoft_stop();
			break;
			
		case I2C_STATUS_BUS_ERROR:
			uart_send_char('B');
			break;

		case TW_ST_SLA_ACK: // 0xA8: SLA+R received, ACK returned
        case TW_ST_DATA_ACK:    // 0xB8: data transmitted, ACK received
			uart_send_char('D');
			b = i2csoft_read_byte();
			uart_send_int(b);
			uart_send_char(' ');
			TWDR = b;
            break;
 
        case TW_ST_DATA_NACK:   // 0xC0: data transmitted, NACK received
        case TW_ST_LAST_DATA:   // 0xC8: last data byte transmitted, ACK received
			//b = i2csoft_read_byte(false);
			uart_send_char('L');
			break;
			
		default:
			uart_send_char('U');
			uart_send_int(status);
			uart_send_char(' ');
			break;
	}
	TWCR |= (1<<TWINT);
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
