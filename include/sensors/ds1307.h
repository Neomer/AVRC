#ifndef DS1307
#define DS1307
	
#define DS1307_REGISTER_SECONDS			0x00
#define		DS1307_SECONDS_MASK_LOW		0x0F
#define		DS1307_SECONDS_MASK_HIGH	0x70
#define DS1307_REGISTER_MINUTES			0x01
#define DS1307_REGISTER_HOURS			0x02
#define DS1307_REGISTER_DOW				0x03 // Day of a week
#define DS1307_REGISTER_DAY				0x04 
#define DS1307_REGISTER_MONTH			0x05
#define DS1307_REGISTER_YEAR			0x06
#define DS1307_REGISTER_CONTROL			0x07
#define DS1307_REGISTER_SRAM			0x08

#include <interface/i2c.h>

inline void ds1307_init()
{
	i2c_init_master(72);
}

void ds1307_read_register(uint8_t address)
{
	i2c_write_byte(address);
}

void ds1307_write_register(uint8_t address, uint8_t value)
{
	
}

#endif // DS1307

