#ifndef BMP280_H
#define BMP280_H

#include <avr/io.h>
#include <util/delay.h> 
#include <stdio.h>

#include <interface/i2c.h>
#include <interface/spi.h>
#include <interface/uart.h>

#ifndef BMP280_SDO
#define BMP280_SDO					0x01
#endif

#define BMP280_R					0xEF
#define BMP280_W					0xEE

#define BMP280_REG_CHIPID			0xD0
#define BMP280_REG_RESET			0xE0

#define BMP280_I2C_ADDRESS_1		0xEE 
#define BMP280_I2C_ADDRESS_2		0xEC

#define BMP280_POWER_ON_RESET		0xB6

#define	BMP280_REG_CONTROL			0xF4
#define	BMP280_REG_CONFIG			0xF5

#define	BMP280_REG_RESULT_PRESSURE			0xF7			// 0xF7(msb) , 0xF8(lsb) , 0xF9(xlsb) : stores the pressure data.
#define BMP280_REG_RESULT_TEMPRERATURE		0xFA		// 0xFA(msb) , 0xFB(lsb) , 0xFC(xlsb) : stores the temperature data.

#define	BMP280_OVERSAMPLING_T1		0x20
#define	BMP280_OVERSAMPLING_T2		0x40
#define	BMP280_OVERSAMPLING_T4		0x60
#define	BMP280_OVERSAMPLING_T8		0x80
#define	BMP280_OVERSAMPLING_T16		0xA0

#define	BMP280_OVERSAMPLING_P1		0x04
#define	BMP280_OVERSAMPLING_P2		0x08
#define	BMP280_OVERSAMPLING_P4		0x0C
#define	BMP280_OVERSAMPLING_P8		0x10
#define	BMP280_OVERSAMPLING_P16		0x14

#define	BMP280_MODE_SLEEP			0x00
#define	BMP280_MODE_FORCED			0x01
#define	BMP280_MODE_NORMAL			0x03

#define	BMP280_TSB_0_5				0x00
#define	BMP280_TSB_62_5				0x20
#define	BMP280_TSB_125				0x40
#define	BMP280_TSB_250				0x60
#define	BMP280_TSB_500				0x80
#define	BMP280_TSB_1000				0xA0
#define	BMP280_TSB_2000				0xC0
#define	BMP280_TSB_4000				0xE0

#define	BMP280_FILTER_OFF			0x00
#define	BMP280_FILTER_COEFFICIENT2	0x04
#define	BMP280_FILTER_COEFFICIENT4	0x08
#define	BMP280_FILTER_COEFFICIENT8	0x0C
#define	BMP280_FILTER_COEFFICIENT16	0x10

#define	BMP280_SPI_OFF	0x00
#define	BMP280_SPI_ON	0x01

#define BMP280_W_REGISTER			0x7F
#define BMP280_R_REGISTER			0x80

#define	BMP280_MEAS			(BMP280_OVERSAMPLING_T16 | BMP280_OVERSAMPLING_P16 | BMP280_MODE_NORMAL)
#define	BMP280_CONFIG		(BMP280_TSB_0_5 | BMP280_FILTER_COEFFICIENT8 | BMP280_SPI_OFF)

#ifdef AVRC_SPI
inline void bmp280_spi_init()
{
	spi_init_master();
}

inline void bmp280_spi_register_write( uint8_t address, uint8_t value)
{
	spi_fast_exchage(address & BMP280_W_REGISTER);
	spi_fast_exchage(value);
}

inline uint8_t bmp280_spi_register_read( uint8_t address )
{
	uint8_t ret = spi_fast_exchage(address | BMP280_R_REGISTER);
	return ret;
}
#endif

#ifdef AVRC_I2C

inline void bmp280_i2c_init(uint8_t speed)
{
	i2c_init_master(speed, false, I2C_IC_ADDRESS);
}

inline uint8_t bmp280_i2c_register_read(uint8_t address)
{
	uart_send_str("begin read\n");
	
	uint8_t err = 0xFF;
	i2c_start(&err);
	if (err != 0xFF) 
	{
		uart_send_str("start error!\n");
		return err;
	}
	uart_send_str("start sent\n");
	i2c_write_byte(BMP280_I2C_ADDRESS_1);
	i2c_write_byte(address);
	i2c_write_byte(BMP280_I2C_ADDRESS_1 | 0x01);
	uint8_t ret = i2c_read_byte();
	i2c_stop();
	
	return ret;
}

inline void bmp280_i2c_register_write(uint8_t address, uint8_t data)
{
	i2c_start();
	i2c_write_byte(BMP280_I2C_ADDRESS_1);
	i2c_write_byte(address);
	i2c_write_byte(data);
	i2c_stop();
}
#endif

#endif // BMP280_H
