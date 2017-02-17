#ifndef BCD
#define BCD

#include <inttypes.h>

inline uint8_t bcd_decode(uint8_t value)
{
	return (((value & 0xF0) >> 4) * 10) + (value & 0x0F);
}

inline uint8_t bcd_encode(uint8_t value)
{
	return ((value / 16) * 10) + (value % 16);
}

inline uint8_t bcd_encode2(uint8_t value)
{
	uint8_t ret = 0, idx = 0;
	while (value > 0)
	{
		ret |= (value % 10) << ((idx++) * 4);
		value = value * 0.1;
	}
	return ret;
}

#endif // BCD

