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

#define I2C_SPEED_4MHz_100KHz		16
#define I2C_SPEED_4MHz_400KHz		1

#define I2C_SPEED_8MHz_100KHz		32
#define I2C_SPEED_8MHz_400KHz		2

#define I2C_SPEED_16MHz_100KHz		64
#define I2C_SPEED_16MHz_400KHz		4

///
/// \brief i2c_init_master Включает на МК интерфейс I2C (TWI) в режиме мастера
/// \param speed Скорость по формуле  ((F_CPU / <bitrate>) - 16)/2 = 72 
/// \param allow_broadcast Разрешает МК отвечать на широковещательный запрос с адресом 0x00
/// \param address Адрес МК в сети
///
inline void i2c_init_master(uint8_t speed, bool allow_broadcast = false, uint8_t address = 0x00)
{
	TWBR = speed;
	TWSR = 0;
//	TWAR = (address << 1) | (allow_broadcast);
}
						

inline uint8_t i2c_start()
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
	return TWSR;
}

inline bool i2c_open_read(uint8_t address)
{
	TWDR = address << 1;
	TWCR = (1<<TWINT) | (1<<TWEN); 
	i2c_waitFlag;
}

inline bool i2c_open_write(uint8_t address)
{
	TWDR = ((address << 1) | 1);
	TWCR = (1<<TWINT) | (1<<TWEN); 
	i2c_waitFlag;
}

inline void i2c_write_byte(uint8_t data)
{	
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN); 
	i2c_waitFlag;
}

inline void i2c_write_data(uint8_t *data, uint8_t length)
{
	while (length--)
	{
		TWDR = *(data++);
		TWCR = (1<<TWINT) | (1<<TWEN); 
		i2c_waitFlag;
	}
}

inline uint8_t i2c_read_byte( void )
{
	TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
	i2c_waitFlag;
	return TWDR;
}

inline void i2c_read_data(uint8_t *data, uint8_t length)
{
	while (length--)
	{
		TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
		i2c_waitFlag;
		*(data++) = TWDR;
	}
}


inline void i2c_stop()
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN); 
}

#endif // I2C

