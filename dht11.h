#ifndef DHT11
#define DHT11

#include <inttypes.h>
#include <util/delay.h>
#include "MemMath.h"

#define dht11_read(ddr, port, pin, bit, data, temp, hum, check) \
	setHigh(ddr, bit); \
	setLow(port, bit); \
	_delay_ms (50); \
	setHigh(port, bit); \
	setLow(ddr, bit); \
	while (bitIsHigh(pin, bit));	\
	while (bitIsLow(pin, bit));	\
	while (bitIsHigh(pin, bit));	\
	for (int b = 0; b < 5; b++)	{	\
		for (int bitc = 0; bitc < 8; bitc++) {	\
			while (bitIsLow(pin, bit));	\
			_delay_us (50);	\
			if (bitIsHigh(pin, bit))	\
				data[b] |= 1 << (7 - bitc);	\
			while (bitIsHigh(pin, bit));	\
		}	\
	}	\
	_delay_us(70);	\
	setHigh(ddr, bit);	\
	setHigh(port, bit);	\
	hum = data[0];	\
	temp = data[2];	\
	check = data[0] + data[1] + data[2] + data[3] == data[4];

#endif // DHT11

