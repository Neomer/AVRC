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

#define I2C_STATUS_MASK					0xF8
#define I2C_STATUS_BUS_ERROR			0x00

#define I2C_STATUS_MT_START				0x08
#define I2C_STATUS_MT_REPSTART			0x10
#define I2C_STATUS_MT_ARB_LOST			0x38
#define I2C_STATUS_MT_TX_ADR_ACK		0x18
#define I2C_STATUS_MT_TX_ADR_NACK		0x20
#define I2C_STATUS_MT_TX_DATA_ACK		0x28
#define I2C_STATUS_MT_TX_DATA_NACK		0x30
#define I2C_STATUS_MT_RX_DATA_ACK		0x50
#define I2C_STATUS_MT_RX_DATA_NACK		0x58
#define I2C_STATUS_MT_RX_ADR_ACK		0x40
#define I2C_STATUS_MT_RX_ADR_NACK		0x48

#define I2C_STATUS_SR_RX_ADR_ACK		0x60
#define I2C_STATUS_SR_RX_ADR_NACK		0x68
#define I2C_STATUS_SR_RX_DATA_ACK		0x80
#define I2C_STATUS_SR_RX_DATA_NACK		0x88
#define I2C_STATUS_SR_RX_STOP_RESTART	0xA0

#define I2C_STATUS_ST_ADR_ACK			TW_ST_SLA_ACK
#define I2C_STATUS_ST_ADR_NACK			TW_ST_ARB_LOST_SLA_ACK
#define I2C_STATUS_ST_DATA_ACK			TW_ST_DATA_ACK
#define I2C_STATUS_ST_DATA_NACK			TW_ST_DATA_NACK
#define I2C_STATUS_ST_LAST_DATA			TW_ST_LAST_DATA


#define I2C_SPEED_4MHz_100KHz		16
#define I2C_SPEED_4MHz_400KHz		1

#define I2C_SPEED_8MHz_50KHz		72
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
}

inline void i2c_init_slave(uint8_t speed, uint8_t address)
{
//	TWBR = speed;
	TWSR = 0;
	TWAR = address << 1;
	TWCR = 0<<TWSTA|0<<TWSTO|1<<TWINT|1<<TWEA|1<<TWEN|1<<TWIE;
}
						

inline uint8_t i2c_start()
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while(!(TWCR & (1<<TWINT)));
	uint8_t s = TWSR & I2C_STATUS_MASK;
	if ((s != I2C_STATUS_MT_START) && (s != I2C_STATUS_MT_REPSTART))
	{
		uart_send_str("start error");
	}
	return s ;
}

inline bool i2c_open_read(uint8_t address)
{
	TWDR = ((address << 1) | 1);
	TWCR = (1<<TWINT) | (1<<TWEN); 
	i2c_waitFlag;
	uint8_t s = TWSR & I2C_STATUS_MASK;
	if ((s != I2C_STATUS_MT_RX_ADR_ACK))
	{
		uart_send_str("i2c_open_read() error ");
		uart_send_int(s);
	}
}

inline bool i2c_open_write(uint8_t address)
{
	TWDR = address << 1;
	TWCR = (1<<TWINT) | (1<<TWEN); 
	i2c_waitFlag;
	uint8_t s = TWSR & I2C_STATUS_MASK;
	if ((s != I2C_STATUS_MT_TX_ADR_ACK))
	{
		uart_send_str("i2c_open_write() error ");
		uart_send_int(s);
	}
}

inline void i2c_write_byte(uint8_t data)
{	
	i2c_waitFlag;
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN); 
	i2c_waitFlag;
	uint8_t s = TWSR & I2C_STATUS_MASK;
	if ((s != I2C_STATUS_MT_RX_DATA_ACK)&&(s != I2C_STATUS_MT_TX_DATA_ACK))
	{
		uart_send_str("data error ");
		uart_send_int(s);
	}
}

inline void i2c_write_array(uint8_t *data, uint8_t length)
{
	while (length--)
	{
		uart_send_char('>');
		uart_send_int(*data);
		TWDR = *(data++);
		TWCR = (1<<TWINT) | (1<<TWEN); 
		i2c_waitFlag;
	}
}

inline void i2c_write_str(char *data)
{
	char *ptr = data;
	while ((*ptr))
	{
		TWDR = *(ptr++);
		TWCR = (1<<TWINT) | (1<<TWEN); 
		i2c_waitFlag;
	}
}


inline uint8_t i2c_read_byte( void )
{
	TWCR = (1<<TWINT)|(0<<TWEA)|(1<<TWEN);
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
		uart_send_char('<');
		
	}
}


inline void i2c_stop()
{
	TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN); 
}

#endif // I2C

