#ifndef I2C
#define I2C

#define AVRC_I2C

#include <MemMath.h>
#include <avr/io.h>
#include <util/twi.h>
#include <util/delay.h>
#include <interface/uart.h>

#define i2c_waitFlag			while(!(TWCR & (1<<TWINT)))

#define I2C_IC_ADDRESS			0xE6

#define I2C_STATUS_MASK			0xFC
#define I2C_STATUS_START		0x08
#define I2C_STATUS_REPSTART		0x10


///
/// \brief i2c_init_master Включает на МК интерфейс I2C (TWI) в режиме мастера
/// \param speed Скорость по формуле  ((F_CPU / <bitrate>) - 16)/2 = 72 
/// \param allow_broadcast Разрешает МК отвечать на широковещательный запрос с адресом 0x00
/// \param address Адрес МК в сети
///
void i2c_init_master(uint8_t speed, bool allow_broadcast = false, uint8_t address = 0x00)
{
	TWBR = speed;
	TWSR = 0;
//	TWAR = (address << 1) | (allow_broadcast);
//	TWCR =  (1 << TWEN) |			// enable twi
//			(0 << TWIE);			// disable interrupts
}
						

void i2c_start(uint8_t *error = 0)
{
//	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
//	uart_send_str("Control register set\n");
//	i2c_waitFlag;
//	uart_send_str("Flag received!\n");
//	uint8_t status = TWSR & I2C_STATUS_MASK;
//    if (!((status & I2C_STATUS_START) || (status & I2C_STATUS_REPSTART)))
//	{
//		if (error) *error = status;
//    }

	uart_send_str("Control register set!\n");
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
	uart_send_str("Flag received!\n");
}

void i2c_write_byte(uint8_t data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN); 
	i2c_waitFlag;
}

uint8_t i2c_read_byte( void )
{
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	return TWDR;
}

void i2c_stop()
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN); 
}

#endif // I2C

