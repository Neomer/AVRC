#ifndef DS1307
#define DS1307

#define DS1307_I2C_ADDRESS				0xD0

#define DS1307_REGISTER_SECONDS			0x00
#define		DS1307_SECONDS_MASK_LOW		0x0F
#define		DS1307_SECONDS_HIGH_DISP	4
#define		DS1307_SECONDS_MASK_HIGH	0x70
#define		DS1307_START				7
#define DS1307_REGISTER_MINUTES			0x01
#define		DS1307_MINUTES_MASK_LOW		0x0F
#define		DS1307_MINUTES_HIGH_DISP	4
#define		DS1307_MINUTES_MASK_HIGH	0x70
#define DS1307_REGISTER_HOURS			0x02
#define		DS1307_HOURS_MASK_LOW		0x0F
#define		DS1307_HOURS_HIGH_DISP		4
#define		DS1307_HOURS_MASK_HIGH_12	0x10
#define		DS1307_HOURS_MASK_HIGH_24	0x30
#define		DS1307_HOURS_12_24			6
#define		DS1307_HOURS_AM_PM			5
#define DS1307_REGISTER_DOW				0x03 // Day of a week
#define		DS1307_DOW_MASK				0x07
#define DS1307_REGISTER_DAY				0x04 
#define		DS1307_DAY_MASK_LOW			0x0F
#define		DS1307_DAY_HIGH_DISP		4
#define		DS1307_DAY_MASK_HIGH		0x30
#define DS1307_REGISTER_MONTH			0x05
#define		DS1307_MONTH_MASK_LOW		0x0F
#define		DS1307_MONTH_HIGH_DISP		4
#define		DS1307_MONTH_MASK_HIGH		0x10
#define DS1307_REGISTER_YEAR			0x06
#define		DS1307_YEAR_MASK_LOW		0x0F
#define		DS1307_YEAR_HIGH_DISP		4
#define		DS1307_YEAR_MASK_HIGH		0xF0
#define DS1307_REGISTER_CONTROL			0x07
#define DS1307_REGISTER_SRAM			0x08

#include <MemMath.h>
#include <interface/i2c.h>
#include <core/DateTime.h>
#include <core/BCD.h>

void ds1307_read_register(uint8_t address)
{
	i2c_start();
	i2c_open_read(DS1307_I2C_ADDRESS);
	i2c_write_byte(address);
	uint8_t ret = i2c_read_byte();
	i2c_stop();
	return ret;
}

void ds1307_write_register(uint8_t address, uint8_t value)
{
	i2c_start();
	i2c_open_read(DS1307_I2C_ADDRESS);
	i2c_write_byte(address);
	i2c_write_byte(value);
	i2c_stop();
}

inline void ds1307_init()
{
	i2c_init_master(I2C_SPEED_8MHz_100KHz);
}

void ds1307_start()
{
	uint8_t st = ds1307_read_register(DS1307_REGISTER_SECONDS);
	setLow(st, DS1307_START);
	ds1307_write_register(DS1307_REGISTER_SECONDS, st);
}

void ds1307_getDT(DateTime *dt)
{
	uint8_t buf[7];
	
	i2c_start();
	i2c_open_read(DS1307_I2C_ADDRESS);
	i2c_write_byte(DS1307_REGISTER_SECONDS);
	i2c_read_data(buf, 7);
	i2c_stop();
	
	dt->seconds = bcd_decode(buf[0]);
	dt->minutes = bcd_decode(buf[1]);
	if (bitIsHigh(buf[2], DS1307_HOURS_12_24))
	{
		if (bitIsHigh(buf[2], DS1307_HOURS_AM_PM))
		{
			dt->hours = (((buf[2] & DS1307_HOURS_MASK_HIGH_12) >> DS1307_HOURS_HIGH_DISP) + 12) * 10 + 
					(buf[2] & DS1307_HOURS_MASK_LOW);
		}
		else
		{
			dt->hours = ((buf[2] & DS1307_HOURS_MASK_HIGH_12) >> DS1307_HOURS_HIGH_DISP) * 10 + 
					(buf[2] & DS1307_HOURS_MASK_LOW);
		}
	}
	else
	{
		dt->hours = bcd_decode(buf[2]);
	}
	dt->dayOfWeek = bcd_decode(buf[3]);
	dt->day	  = bcd_decode(buf[4]);
	dt->month = bcd_decode(buf[5]);
	dt->year  = bcd_decode(buf[6]);
}

void ds1307_setDT(DateTime *dt)
{
	uint8_t buf[7];
	buf[0] = bcd_encode(dt->seconds);
	buf[1] = bcd_encode(dt->minutes);
	buf[2] = bcd_encode(dt->hours);
	buf[3] = bcd_encode(dt->dayOfWeek);
	buf[4] = bcd_encode(dt->day);
	buf[5] = bcd_encode(dt->month);
	buf[6] = bcd_encode(dt->year);
	
	i2c_start();
	i2c_open_write(DS1307_I2C_ADDRESS);
	i2c_write_byte(DS1307_REGISTER_SECONDS);
	i2c_write_data(buf, 7);
	i2c_stop();
}

#endif // DS1307

